#include "stepperMotor.h"


int waveStep[8][4] = {        
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1},
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1}
};


void StepperControlForward()
{
    for (int step = 0; step < 8 ; step++)
    {
        STEPPER_INPUT_1 = waveStep[step][0];
        delayMs(1);
        STEPPER_INPUT_2 = waveStep[step][1];
        delayMs(1);
        STEPPER_INPUT_3 = waveStep[step][2];
        delayMs(1);
        STEPPER_INPUT_4 = waveStep[step][3];
        delayMs(1);
    }
}


void StepperControlBackward()
{
    for (int step = 7; step >= 0 ; step--)
    {
        STEPPER_INPUT_4 = waveStep[step][3];
        delayMs(1);
        STEPPER_INPUT_3 = waveStep[step][2];
        delayMs(1);
        STEPPER_INPUT_2 = waveStep[step][1];
        delayMs(1);
        STEPPER_INPUT_1 = waveStep[step][0];
        delayMs(1);
    }
}