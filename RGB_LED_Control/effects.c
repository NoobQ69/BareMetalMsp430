#include "effects.h"

unsigned int Pwm = 40, Ms = 20, LoopRange = 50;
unsigned char HasChanged = 0;

void effect1(void)
{
    for (int i = 0; i < LoopRange; i++) {
      RED_LED_TIMER += Pwm;
      if (HasChanged) {HasChanged = 0; return;}
      delayMs(Ms);
    }
    
    for (int i = 0; i < LoopRange; i++) {
      GREEN_LED_TIMER += Pwm;
      if (HasChanged) {HasChanged = 0; return;}
      delayMs(Ms);
    }
    
    for (int i = 0; i < LoopRange; i++) {
      BLUE_LED_TIMER += Pwm;
      if (HasChanged) {HasChanged = 0; return;}
      delayMs(Ms);
    }
}

void effect2(void)
{
    BLUE_LED_TIMER = 2000;
    for (int i = 0; i < LoopRange; i++) {
      BLUE_LED_TIMER -= Pwm;
      RED_LED_TIMER += Pwm;
      if (HasChanged) {HasChanged = 0; return;}
      delayMs(Ms);
    }
    
    for (int i = 0; i < LoopRange; i++) {
      RED_LED_TIMER -= Pwm;
      GREEN_LED_TIMER += Pwm;
      if (HasChanged) {HasChanged = 0; return;}
      delayMs(Ms);
    }
    
    for (int i = 0; i < LoopRange; i++) {
      GREEN_LED_TIMER -= Pwm;
      BLUE_LED_TIMER += Pwm;
      if (HasChanged) {HasChanged = 0; return;}
      delayMs(Ms);
    }
}

void effect3(void)
{
    for (int i = 0; i < LoopRange; i++) {
      GREEN_LED_TIMER += Pwm;
      RED_LED_TIMER   += Pwm;
      if (HasChanged) {HasChanged = 0; return;}
      delayMs(Ms);
    }
    
    GREEN_LED_TIMER = 0x00;
    RED_LED_TIMER = 0x00;
    
    for (int i = 0; i < LoopRange; i++) {
      GREEN_LED_TIMER += Pwm;
      BLUE_LED_TIMER  += Pwm;
      if (HasChanged) {HasChanged = 0; return;}
      delayMs(Ms);
    }
    
    GREEN_LED_TIMER = 0x00;
    BLUE_LED_TIMER = 0x00;
    
    for (int i = 0; i < LoopRange; i++) {
      BLUE_LED_TIMER += Pwm;
      RED_LED_TIMER  += Pwm;
      if (HasChanged) {HasChanged = 0; return;}
      delayMs(Ms);
    }
}

void effect4(void)
{
    BLUE_LED_TIMER = 0;
    RED_LED_TIMER = 2000;
    for (int i = 0; i < LoopRange; i++) {
      BLUE_LED_TIMER += Pwm;
      delayMs(Ms);
      if (HasChanged) {HasChanged = 0; return;}
      delayMs(Ms);
    }
    
    BLUE_LED_TIMER = 2000;
    RED_LED_TIMER = 0;
    for (int i = 0; i < LoopRange; i++) {
      RED_LED_TIMER += Pwm;
      delayMs(Ms);
      if (HasChanged) {HasChanged = 0; return;}
      delayMs(Ms);
    }
    
    RED_LED_TIMER = 0;
    
    BLUE_LED_TIMER = 0;
    GREEN_LED_TIMER = 2000;
    for (int i = 0; i < LoopRange; i++) {
      BLUE_LED_TIMER += Pwm;
      delayMs(Ms);
      if (HasChanged) {HasChanged = 0; return;}
      delayMs(Ms);
    }
    
    BLUE_LED_TIMER = 2000;
    GREEN_LED_TIMER = 0;
    for (int i = 0; i < LoopRange; i++) {
      GREEN_LED_TIMER += Pwm;
      delayMs(Ms);
      if (HasChanged) {HasChanged = 0; return;}
      delayMs(Ms);
    }
    
    GREEN_LED_TIMER = 0;
}