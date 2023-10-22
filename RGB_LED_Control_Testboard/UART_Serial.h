#ifndef __UART_SERIAL_H_
#define __UART_SERIAL_H_

#include "main.h"

void UART_Send_Byte(unsigned char byte);
void UART_Send_String(char *stringToSend);
void UART_Send_Number(unsigned int number);

#endif