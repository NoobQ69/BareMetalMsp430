#include "BMP180.h"

int BMP180_ReadRawTemperature()
{
    unsigned char data[] = {0x00, 0x2E}; // Start temperature measurement
    I2C_MasterTransmitData(data, sizeof(data)/sizeof(data[0]));
    delayMs(5); // Wait for measurement to complete
    data[0] = 0x00;
    data[1] = 0x00;
    I2C_MasterTransmitData(data, 1); // Send register address to read from
    I2C_MasterReceiveData(data, 2); // Read 2 bytes of temperature data
    int rawTemperature = ((int)data[0] << 8) | (int)data[1];
    return rawTemperature;
}

long BMP180_ReadRawPressure()
{
    unsigned char data[] = {0x00, 0x34 | (3 << 6)}; // Start pressure measurement (high resolution mode)
    I2C_MasterTransmitData(data, sizeof(data)/sizeof(data[0]));
    delayMs(26); // Wait for measurement to complete
    data[0] = 0x00;
    data[1] = 0x00;
    data[2] = 0x00;
    I2C_MasterTransmitData(data, 1); // Send register address to read from
    I2C_MasterReceiveData(data, 3); // Read 3 bytes of pressure data
    long rawPressure = ((long)data[0] << 16) | ((long)data[1] << 8) | (long)data[2];
    rawPressure = rawPressure >> (8 - 3); // Right-shift by 3 bits (since we're using high resolution mode)
    return rawPressure;
}

int BMP180_GetTemperature()
{
    int rawTemperature = BMP180_ReadRawTemperature();
    int X1 = ((rawTemperature - 0x000AC6) * 0x000D) >> 8;
    int X2 = ((int)(rawTemperature - 0x000AC6) * (int)(rawTemperature - 0x000AC6) * (int)0x0B5) >> 16;
    return X1 + X2 + 0x01C0; // Return temperature in 0.1 degrees Celsius
}

long BMP180_GetPressure()
{
    long rawPressure = BMP180_ReadRawPressure();
    int X1 = ((int)BMP180_GetTemperature() - 0x000C0) * 0x0010;
    int X2 = (rawPressure - 0x00800000) >> 11;
    int X3 = ((int)BMP180_GetTemperature() - 0x000C0) * ((int)BMP180_GetTemperature() - 0x000C0) * 0x0008;
    int B3 = (((int)(rawPressure >> 2)) - X2 - X3) * 0x0001 + 0x08000;
    B3 = B3 >> 4;
    int B4 = (((int)(rawPressure >> 2)) - X2 - X3) * 0x0001 + 0x08000;
    B4 = ((B4 >> 2) * 0x0025) >> 10;
    int B7 = ((int)(rawPressure >> 2) - X2 - X3) * 0x0001;
    if (B7 < 0x80000000)
        B7 = (B7 << 1) / B3;
    else
        B7 = (B7 / B3) << 1;
    int X4 = (B4 * (int)(B7 * B7 / 0x08000)) >> 12;
    int X5 = (int)B7 * 0x4000;
    int X6 = (int)(B3 * X4) >> 11;
    long B = X5 + X6;
    B = B + 0x00008000;
    B = B >> 15;
    return B;
}