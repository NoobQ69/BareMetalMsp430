#include "main.h"

unsigned char state, direction, LEDState;
unsigned char groupNumber = 8;

void SystemClockInit()
{
    BCSCTL1 = CALBC1_8MHZ;      // Set DCO range select to 8 MHz
    DCOCTL = CALDCO_8MHZ;       // Set DCO frequency control to 8 MHz
    BCSCTL2 = 0x06;             // Set SMCLK source select to DCO/8 (8 MHz)
}

void GPIOInit()
{
    // SRCLK + SER + RCLK + CTL1 + CTL2
    P1DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4;
    
    // IN1 + IN2 + IN3 + IN4 of stepper motor
    P2DIR |= BIT0 + BIT1 + BIT2 + BIT3;
    
    // for buttons
    P1REN |= BIT5 + BIT6;
    P1OUT |= BIT5 + BIT6;
}

void ControlStepperMotor()
{
    displayLED7Mpx2(groupNumber, LEDState);
    readStateButton();
    readDirectionButton();
    
    if (state == 1)
    {
        if (direction == 1)
        {
          StepperControlForward();
        }
        else
        {
          StepperControlBackward();
        }
    }
}

int main( void )
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    SystemClockInit();
    GPIOInit();
    while (1)
    {
      ControlStepperMotor();
    }
    //return 0;
}
