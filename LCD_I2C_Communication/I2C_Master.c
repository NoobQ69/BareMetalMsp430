#include "I2C_Master.h"

unsigned char err = 0;

void I2C_MasterModeInit()
{
  UCB0CTL1 |= UCSWRST;                         // Reset I2C
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;        // I2C Master, SMCLK and synchronous mode;
  UCB0CTL1 = UCSSEL_2 + UCSWRST;                 // Using SMCLK, transmiter mode and keep SW reset
  UCB0BR0 = 10;                                // fSCL = SMCLK/10 = ~100kHz
  UCB0BR1 = 0;
  UCB0CTL1 &= ~UCSWRST;                         // Clear SW reset, resume operation
  IE2 |= UCB0TXIE + UC0RXIE;
}

void I2C_MasterStoreSlaveAddress(unsigned char slaveAddress, unsigned char slaveMode)
{
  UCB0I2CSA = slaveAddress;
  if (slaveMode == 10)
    UCB0CTL0 |= UCSLA10;
}

void I2C_MasterTransmitData(unsigned char *data, unsigned char length)
{
  for (unsigned char i = 0; i < length; i++) 
  {
    UCB0CTL1 |= UCTR + UCTXSTT;
    while (!(IFG2 & UCB0TXIFG));                // Wait until transmit is complete
    IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
    
    UCB0TXBUF = data[i];                        // Load data into transmit buffer
    while (!(IFG2 & UCB0TXIFG));                // Wait until transmit is complete
    
    UCB0CTL1 |= UCTXSTP;                       // Set STOP condition bit
    while (UCB0CTL1 & UCTXSTP);                // Wait until STOP condition is sent
    IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
    
    if (UCB0STAT & UCNACKIFG)                   // Check for NACK
    {
      // Handle NACK here
      err = 1;
      break;
    }
  }
}

void I2C_MasterReceiveData(unsigned char *data, unsigned char length)
{
  for (unsigned char i = 0; i < length; i++) 
  {
    UCB0CTL1 |= UCTXSTT;
    while (!(IFG2 & UCB0RXIFG));                // Wait until transmit is complete
    IFG2 &= ~UCB0TXIFG;                         // Clear USCI_B0 TX int flag
    
    data[i] = UCB0RXBUF;                        // Load data into transmit buffer
    while (!(IFG2 & UCB0RXIFG));                // Wait until transmit is complete
    
    UCB0CTL1 |= UCTXSTP;                        // Set STOP condition bit
    while (UCB0CTL1 & UCRXSTP);                 // Wait until STOP condition is sent
    IFG2 &= ~UCB0RXIFG;                         // Clear USCI_B0 TX int flag
    
    if (UCB0STAT & UCNACKIFG)                   // Check for NACK
    {
      // Handle NACK here
      err = 1;
      break;
    }
  }
}