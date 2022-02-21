/*
*   Serial I/O interface for HAL
*   Retargets _write and _read to use serial for use with stdio
*
*   Author: Will Merges
*/
#include "sio.h"
#include "usart.h"
#include "common.h"
#include "queue.h"
#include "ringbuff.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static queue_t* tx_queue[NUM_UARTS];

static uint8_t rx_byte[NUM_UARTS];
static uint8_t rx_buffer[NUM_UARTS][RX_BUFFER_SIZE];
static ringbuff_t rx_rb[NUM_UARTS];

void (*callback_funcs[NUM_UARTS]) ();

// message type used for queueing messages
typedef struct {
    uint8_t* data;
    uint16_t len;
} msg_node_t;

// does initialization for using the sys library
// returns -1 on failure, 1 otherwise
int sio_init() {
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

    if(callback_funcs[i]) {
        callback_funcs[i]();
    }

    HAL_UART_Receive_IT(uarts[i], &(rx_byte[i]), 1);
}


// nonblocking, initiates a DMA transfer or queues it if the UART controller is busy
int sio_write(int fd, char *buff, int len) {
    if(fd >= NUM_UARTS || fd < 0) {
        // invalid index
        return -1;
    }

    msg_node_t* msg = (msg_node_t*)malloc(sizeof(msg_node_t));
    msg->data = (uint8_t*)malloc(sizeof(char) * len);
    memcpy(msg->data, buff, len);
    msg->len = len;

    disable_irq;

    // if tx_ready is true, queue is always empty
    if(QUEUE_EMPTY(tx_queue[fd])) {
        // we can send right away
        q_enqueue(tx_queue[fd], msg);
        HAL_UART_Transmit_DMA(uarts[fd], msg->data, len);
    } else {
        q_enqueue(tx_queue[fd], msg);
    }

    enable_irq;

    return len;
}


// read a certain amount of characters
// returns amount of characters actually read up to length len
int sio_read(int fd, char* buff, int len) {
    if(fd >= NUM_UARTS || fd < 0) {
        // invalid index
        return -1;
    }

    if(len < 0) {
        // invalid
        return -1;
    }

    // will return actual number of bytes we can read
    return rb_memcpyout((uint8_t*)buff, &(rx_rb[fd]), len);
}

int _write(int fd, char* buff, int len) __attribute__((alias("sio_write")));
int _read(int fd, char* buff, int len) __attribute__((alias("sio_read")));

// return how many bytes are available
size_t sio_available(int fd) {
    if(fd >= NUM_UARTS || fd < 0) {
        // invalid index
        return 0;
    }

    return rx_rb[fd].len;
}

void sio_attach_callback(int fd, void (*cb_func) ()) {
    if(fd >= NUM_UARTS || fd < 0) {
        // invalid index
        return;
    }

    callback_funcs[fd] = cb_func;
}

int sio_search_fd(const char* name) {
    int fd = -1;
    for(size_t i = 0; i < NUM_UARTS; i++) {
        if(!strcmp(name, uart_names[i])) {
            fd = i;
        }
    }

    return fd;
}
