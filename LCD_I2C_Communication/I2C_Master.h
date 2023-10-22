#ifndef __I2C_MASTER_H_
#define __I2C_MASTER_H_

#include "main.h"
void I2C_MasterModeInit();
void I2C_MasterStoreSlaveAddress(unsigned char slaveAddress, unsigned char slaveMode);
unsigned char I2C_MasterTransmitData(unsigned char *data, unsigned char length, unsigned char registerAddress, unsigned char isWithRegisterAddr);
unsigned char I2C_MasterReceiveData(unsigned char *data, unsigned char length, unsigned char registerAddress, unsigned char isWithRegisterAddr);
void lcd_reset();
#endif