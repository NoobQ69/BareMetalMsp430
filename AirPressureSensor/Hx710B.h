#ifndef __HX710B_H_
#define __HX710B_H_
#include "main.h"

#define HX710B_DIFF1    25      // data rate 10Hz
#define HX710B_TEMP     26      // data rate 40Hz
#define HX710B_DIFF2    27      // data rate 40Hz

#define HX710B_DEFAULT_MODE     HX710B_DIFF2

#define HX710B_OK       0x00U
#define HX710B_ERROR    0x01U
#define HX710B_BUSY     0x02U
#define HX710B_TIMEOUT  0x03U

void Hx710B_Init();
unsigned char Hx710B_ReadAirPressure(unsigned long *data, unsigned int timeOut);
unsigned char Hx710B_IsReady();

#endif