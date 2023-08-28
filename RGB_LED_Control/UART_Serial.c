#include "UART_Serial.h"


void UART_Send_Byte(unsigned char byte)
{
  while (!(IFG2 & UCA0TXIFG));          // Wait until Tx buffer empty (is ready)
  
  UCA0TXBUF = byte;
}

void UART_Send_String(char *stringToSend)
{
  while(*stringToSend) 
  {
    while(!(IFG2 & UCA0TXIFG));
    
    UCA0TXBUF = *stringToSend++;
  }
}

void UART_Send_Number(unsigned int number)
{
  int i = 0;
  unsigned char numberBuffer[6];
  while (number > 0)
  {
    numberBuffer[i++] = (number%10) + '0';
    number /= 10;
  }
  numberBuffer[i] = '0';
  
  while (i >= 0)
  {
    UART_Send_Byte(numberBuffer[i--]);
  }
  UART_Send_Byte('\n');
}

