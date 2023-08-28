#ifndef __BUTTONS_H_
#define __BUTTONS_H_

#include "main.h"

unsigned char readModeState();
unsigned char readEffectsState();
unsigned char readButton(unsigned char (*readState)());
void handleModeButton(void);
void handleEffectsButton(void);

#endif