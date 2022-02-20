/*
*   Retarget the nosys/newlib "syscalls"
*   Without these calling a syscall just calls an empty(?) stub
*/
#include "main.h"
#include "usart.h"
#include "common.h"
#include "queue.h"
#include "ringbuff.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define RX_BUFFER_SIZE 1024 // can buffer reading this many bytes per UART

#define NUM_UARTS 3
static UART_HandleTypeDef* uarts[NUM_UARTS] =
{
    &huart3,
    &huart1, // mapped to "stdout"
    &huart2
};

static queue_t* tx_queue[NUM_UARTS];

static uint8_t rx_byte[NUM_UARTS];
static uint8_t rx_buffer[NUM_UARTS][RX_BUFFER_SIZE];
static ringbuff_t rx_rb[NUM_UARTS];

// message type used for queueing messages
typedef struct {
    uint8_t* data;
    uint16_t len;
} msg_node_t;

// does initialization for using the sys library
// returns -1 on failure, 1 otherwise
int sys_init() {
    // initialize queues
    for(size_t i = 0; i < NUM_UARTS; i++) {
        tx_queue[i] = q_mkqueue(NULL);

        if(!tx_queue[i]) {
            // failure to allocate
            return -1;
        }

        rb_init(&(rx_rb[i]), rx_buffer[i], RX_BUFFER_SIZE, 1);
        HAL_UART_Receive_IT(uarts[i], &(rx_byte[i]), 1);
    }

    return 1;
}


// TX complete, called by the HAL UART IRQ
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    size_t i;
    for(i = 0; i < NUM_UARTS; i++) {
        if(huart == uarts[i]) {
            break;
        }
    }

    #ifdef DEBUG
    printf("software error: got callback for unknown UART\r\n");
    return;
    #endif

    // the message we just sent
    msg_node_t* msg = (msg_node_t*)q_dequeue(tx_queue[i]);
    free(msg->data);
    free(msg);

    // next message to send (if available)
    msg = (msg_node_t*)q_peek(tx_queue[i]);

    if(msg) {
        HAL_UART_Transmit_DMA(uarts[i], msg->data, msg->len);
    }
}


// RX complete, called by the HAL UART IRQ
// TODO probably want to make each uart have a function handle for other things to set
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    size_t i;
    for(i = 0; i < NUM_UARTS; i++) {
        if(huart == uarts[i]) {
            break;
        }
    }

    if(rb_memcpyin(&(rx_rb[i]), &(rx_byte[i]), 1) != 1) {
        #ifdef DEBUG
        printf("unexpected error: ringbuff write failure\r\n");
        #endif

        return;
    }

    // TODO call some user defined callback with the byte we received

    HAL_UART_Receive_IT(uarts[i], &(rx_byte[i]), 1);
}


// retarget _write for stdio functions to use
// nonblocking, initiates a DMA transfer or queues it if the UART controller is busy
// if an error happens it likely won't caught since the function will have already returned
int _write(int file, char *buff, int len) {
    if(file >= NUM_UARTS || file < 0) {
        // invalid index
        return -1;
    }

    msg_node_t* msg = (msg_node_t*)malloc(sizeof(msg_node_t));
    msg->data = (uint8_t*)malloc(sizeof(char) * len);
    memcpy(msg->data, buff, len);
    msg->len = len;

    disable_irq;

    // if tx_ready is true, queue is always empty
    if(QUEUE_EMPTY(tx_queue[file])) {
        // we can send right away
        q_enqueue(tx_queue[file], msg);
        HAL_UART_Transmit_DMA(uarts[file], msg->data, len);
    } else {
        q_enqueue(tx_queue[file], msg);
    }

    enable_irq;

    return len;
}


// read a certain amount of characters
// returns amount of characters actually read up to length len
int _read(int file, char* buff, int len) {
    if(file >= NUM_UARTS || file < 0) {
        // invalid index
        return -1;
    }

    if(len < 0) {
        // invalid
        return -1;
    }

    // will return actual number of bytes we can read
    return rb_memcpyout((uint8_t*)buff, &(rx_rb[file]), len);
}

// return how many bytes are available
size_t io_available(int file) {
    if(file >= NUM_UARTS || file < 0) {
        // invalid index
        return 0;
    }

    return rx_rb[file].len;
}
