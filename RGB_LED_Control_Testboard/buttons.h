#ifndef __BUTTONS__
#define __BUTTONS__

#include "main.h"

unsigned char DigitalRead(unsigned char port, unsigned char pin);
void DigitalWrite(unsigned char port, unsigned char pin, unsigned char value);
unsigned char getPinStatePort(unsigned char port, unsigned char pin);

#endif