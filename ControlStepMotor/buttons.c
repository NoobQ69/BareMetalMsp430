#include "buttons.h"

extern unsigned char state = 1, direction = 1, LEDState = 1;

void readStateButton(void)
{
    if (STATE_BUTTON == 0)
    {
        delayMs(10);
        if (STATE_BUTTON == 0)
        {
            if (state == 0)
            {
              state = 1;
            }
            else
            {
              state = 0;
            }
        }
        while (STATE_BUTTON == 0);
    }
}

void readDirectionButton(void)
{
    if (DIRECTION_BUTTON == 0)
    {
        delayMs(10);
        if (DIRECTION_BUTTON == 0)
        {
            if (direction == 0)
            {
              direction = 1;
              LEDState = 1;
            }
            else
            {
              direction = 0;
              LEDState = 16;
            }
        }
        while (DIRECTION_BUTTON == 0);
    }
}