#include "I2C_Master.h"

void I2C_MasterModeInit()
{
  UCB0CTL1 |= UCSWRST;                         // Reset I2C
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;        // I2C Master, SMCLK and synchronous mode;
  UCB0CTL1 = UCSSEL_2 + UCSWRST;                 // Using SMCLK, transmiter mode and keep SW reset
  UCB0BR0 = 10;                                // fSCL = SMCLK/10 = ~100kHz
  UCB0BR1 = 0;
  UCB0CTL1 &= ~UCSWRST;                         // Clear SW reset, resume operation
  IE2 |= UCB0TXIE + UCB0RXIE;
}

void I2C_MasterStoreSlaveAddress(unsigned char slaveAddress, unsigned char slaveMode)
{
  UCB0CTL1 |= UCSWRST;    
  UCB0I2CSA = slaveAddress;
  UCB0CTL1 &= ~UCSWRST;                 		// Clear SW reset, resume operation 
  
  if (slaveMode == 10)
    UCB0CTL0 |= UCSLA10;
}

unsigned char I2C_MasterTransmitData(unsigned char *data, unsigned char length, unsigned char registerAddress, unsigned char isWithRegisterAddr)
{
  for (unsigned char i = 0; i < length; i++) 
  {
    while (UCB0CTL1 & UCTXSTP);            // Wait until transmit is complete
    UCB0CTL1 |= UCTR + UCTXSTT;
    
    if (isWithRegisterAddr)
    {
      while (!(IFG2 & UCB0TXIFG));            // Wait until transmit is complete
      if(UCB0STAT & UCNACKIFG) return UCB0STAT;	// If transmit error, return the state register
      UCB0TXBUF = registerAddress; 
    }
    
    while (!(IFG2 & UCB0TXIFG));                // Wait until transmit is complete
    if(UCB0STAT & UCNACKIFG) return UCB0STAT;	// If transmit error, return the state register
    UCB0TXBUF = data[i];                        // Load data into transmit buffer
    
    while (!(IFG2 & UCB0TXIFG));                  // Wait until STOP condition is sent
    if(UCB0STAT & UCNACKIFG) return UCB0STAT;	// If transmit error, return the state register
    UCB0CTL1 |= UCTXSTP;                       // Set STOP condition bit
    IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
  }
  return 0;
}

unsigned char I2C_MasterReceiveData(unsigned char *data, unsigned char length, unsigned char registerAddress, unsigned char isWithRegisterAddr)
{
  for (unsigned char i = 0; i < length; i++)
  {
    while (UCB0CTL1 & UCTXSTP);          	// Wait for I2C signal transmit successsfully
    UCB0CTL1 |= UCTR + UCTXSTT;
    
    if (registerAddress)
    {
      while (!(IFG2 & UCB0TXIFG));                // Wait until transmit is complete
      UCB0TXBUF = registerAddress;                        // Clear USCI_B0 TX int flag 
    }

    while (!(IFG2 & UCB0TXIFG));                // Wait until transmit is complete
    
    UCB0CTL1 &= ~UCTR;
    UCB0CTL1 |= UCTXSTP;                        // Set STOP condition bit
    IFG2 &= ~UCB0TXIFG;
    
    while (UCB0CTL1 & UCTXSTT);                 // Wait until STOP condition is sent
    UCB0CTL1 |= UCTXSTP;
    data[i] = UCB0RXBUF;                        // Load data into transmit buffer
  }
}