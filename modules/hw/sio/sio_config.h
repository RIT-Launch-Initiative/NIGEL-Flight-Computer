#ifndef SIO_CONFIG_H
#define SIO_CONFIG_H

#include "usart.h"

#define RX_BUFFER_SIZE 1024 // buffer reading this many bytes per UART

// whichever uart is mapped to index 1 is 'stdout' and used by default in stdio
#define NUM_UARTS 3
static UART_HandleTypeDef* uarts[NUM_UARTS] =
{
    &huart3,
    &huart1,
    &huart2
};

#endif
