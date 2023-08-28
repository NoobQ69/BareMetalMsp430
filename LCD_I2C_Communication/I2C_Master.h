#ifndef __I2C_MASTER_H_
#define __I2C_MASTER_H_

#include "main.h"
void I2C_MasterModeInit();
void I2C_MasterStoreSlaveAddress(unsigned char slaveAddress, unsigned char slaveMode);
void I2C_MasterTransmitData(unsigned char *data, unsigned char length);
void I2C_MasterReceiveData(unsigned char *data, unsigned char length);

#endif