#ifndef __BMP180_H_
#define __BMP180_H_
#include "main.h"

int BMP180_ReadRawTemperature();
long BMP180_ReadRawPressure();
int BMP180_GetTemperature();
long BMP180_GetPressure();

#endif