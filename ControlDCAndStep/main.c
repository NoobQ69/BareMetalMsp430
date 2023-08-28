#include "io430.h"

#define IN1         P1OUT_bit.P5
#define IN2         P2OUT_bit.P0
#define IN3         P2OUT_bit.P1
#define IN4         P2OUT_bit.P2

unsigned char waveStep[4][4] = {{1, 0, 0, 0},
                                {0, 1, 0, 0},
                                {0, 0, 1, 0},
                                {0, 0, 0, 1}};

unsigned char fullStep[4][4] = {{1, 1, 0, 0},
                                {0, 1, 1, 0},
                                {0, 0, 1, 1},
                                {1, 0, 0, 1}};

unsigned char halfStep[8][4] = {{1, 0, 0, 0},
                                {1, 1, 0, 0},
                                {0, 1, 0, 0},
                                {0, 1, 1, 0},
                                {0, 0, 1, 0},
                                {0, 0, 1, 1},
                                {0, 0, 0, 1},
                                {1, 0, 0, 1}};
int kq=1, dk=1, ch_quay=1;

void forwardStep(unsigned char step[][4], unsigned int n)
{
  for (int i = 0; i < n; i++)
  {
    IN1 = step[i][1];
    IN2 = step[i][2];
    IN3 = step[i][3];
    IN4 = step[i][4];
    __delay_cycles(3000);
  }
}

void reverseStep(unsigned char step[][4], unsigned int n)
{
  for (int i = n-1; i >= 0; i--)
  {
    IN1 = step[i][1];
    IN2 = step[i][2];
    IN3 = step[i][3];
    IN4 = step[i][4];
    __delay_cycles(3000);
  }
}


void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  // Cho chan input cua dong co step
  P2DIR |= BIT0 + BIT1 + BIT2;
  P1DIR |= BIT5;
  P2OUT = 0x00;
  
  // Cho nut nhan 
  P1DIR &= ~(BIT0 + BIT1 + BIT4 +BIT7);
  P2DIR &= ~(BIT3 + BIT4 + BIT5);
  
  P1IE |= BIT0 + BIT1 + BIT4 +BIT7;
  P1IES |= BIT0 + BIT1 + BIT4 +BIT7;
  P1IFG &= ~(BIT0 + BIT1 + BIT4 +BIT7);
  
  P2IE |= BIT3 + BIT4 + BIT5;
  P2IES |= BIT3 + BIT4 + BIT5;
  P2IFG &= ~(BIT3 + BIT4 + BIT5);
  
  __bis_SR_register(GIE);
  
  while(1)
  {
    // quay thuan wave
    if((dk==1)&&(ch_quay==1)&&(kq==1))
    {
      forwardStep(waveStep, 4);
    }
    // quay nguoc wave
    if((dk==1)&&(ch_quay==2)&&(kq==1))
    {
        reverseStep(waveStep, 4);
    }
    // quay thuan full
    if((dk==1)&&(ch_quay==1)&&(kq==2))
    {
        forwardStep(fullStep, 4);
    }
    // quay nghich full
    if((dk==1)&&(ch_quay==2)&&(kq==2))
    {
      reverseStep(fullStep, 4);
    }
     // quay thuan half
     if((dk==1)&&(ch_quay==1)&&(kq==3))
    {
      forwardStep(halfStep, 8);
    }
     // quay nguoc half
     if((dk==1)&&(ch_quay==2)&&(kq==3))
    {
      reverseStep(halfStep, 8);
    }   
  }
}

#pragma vector = PORT1_VECTOR
__interrupt void motor_step(void)
{
  if(P1IFG & BIT0)
  {
     dk = 1;
     P1IFG &= ~BIT0;
  }
  
  if(P1IFG & BIT1)
  {
     dk = 0;
     P1IFG &= ~BIT1;
  }
  
  if(P1IFG & BIT4)
  {
     ch_quay = 1;
     P1IFG &= ~BIT4;
  }
  
  if(P1IFG & BIT7)
  {
     ch_quay = 2;
     P1IFG &= ~BIT7;
  }
  if(P2IFG & BIT3)
  {
     kq = 1;
     P2IFG &= ~BIT3;
  } 
  
  if(P2IFG & BIT4)
  {
     kq = 2;
     P2IFG &= ~BIT4;
  }
  
  if(P2IFG & BIT5)
  {
     kq = 3;
     P2IFG &= ~BIT5;
  }
}
