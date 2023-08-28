// khai bao thu vien
#include "io430g2553.h"
#include "stdio.h"
#include "string.h"
// khai bao hang 
int val,giatri;
int xung=0;
unsigned int ReadADC10(int chanel);
int timer = 0;
int counter=0;
int tocdo;
int timer;
int xung;

#define SH_CP    P2OUT_bit.P0
#define DS       P2OUT_bit.P1
#define ST_CP    P2OUT_bit.P2
#define L1       P2OUT_bit.P3
#define L2       P2OUT_bit.P4
#define L3       P2OUT_bit.P5

// khai bao chuong trinh con
void delayms(int ms);
void caidat();
void shiftout(char x);
int  encoder;
// ma anod chung
char so[] = {0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F,0x01,0x19};
int i,j;
// chuong trinh quet led 7seg
void shiftout(char x)
{
  int i;

  for(i = 0; i < 8; i++)
  {
    if(x & (1<<i))
    {
      DS = 1;
    }
    else
    {
      DS = 0;
    }
    SH_CP = 1;
    SH_CP = 0;
  }

}
void delay(int ms)
{
  while(ms--)
    __delay_cycles(1000);
}

void led_encoder()
{
  TA1CTL = TASSEL_2 + ID_3 + MC_1;
  TA1CCTL0 = CCIE;
  TA1CCR0 = 300;
  __bis_SR_register(GIE);
}

void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P2DIR  |= BIT0+BIT1+BIT2+BIT3+BIT4+BIT5; // cau hinh GPIO 7seg voi MSP430
  
  P1DIR |= BIT6; // cau hinh pwm
  P1SEL |= BIT6; // ngo ra pwm P1.6
  // cau hinh PWM
  TACCTL1 = OUTMOD_7;
  TACCR0  = 1050;
  TACTL = TASSEL_2 + MC_1;//SMCLK
  //------------------------------
     
//set P1.3 INPUT Pulse
    P1REN |= BIT3;                                // dien tro keo len
    P1IE |= BIT3;                                //interrupt enable
    P1IES &= ~BIT3;                                // interrupt low-high
 
    P1IFG &= ~BIT3;                                // set interrupt flag to 0 in the beginning
 
    __bis_SR_register(GIE);   // cho phep ngat              
 
    led_encoder();// goi ham led encoder

  while(1){
    // chuong trinh doc encoder
      val = ReadADC10(0); // doc ADC P1.0
      TACCR1 = val; // cho gia tri ADC = TACCR1
      for(int k = 0;k<50;k++){
      for(int h = 0; h < 10;h++){
      L2 = 0;
      ST_CP = 0;
      shiftout(so[tocdo/100]);
      ST_CP = 1;
      // hien thi led thu 2
      L1 = 1;
    //  L3 = 0;
      __delay_cycles(1000);
      L1 = 0;
      ST_CP = 0;
      // tbcb%10 lay phan nguyen
      shiftout(so[(tocdo%100)/10]);
      ST_CP = 1;
      // hien thi led thu 1
      L2 = 1;
     // L3 = 0;
      __delay_cycles(1000);
      L2 = 0; L1 = 0;
      ST_CP = 0;
      // tbcb%10 lay phan nguyen
      shiftout(so[tocdo%10]);
      ST_CP = 1;
      // hien thi led thu 1
      L3 = 1;
  
      __delay_cycles(1000);
      
       L1 = 0;L2 = 0;L3 = 0;
    }
      }
  }
  }

void delayms(int ms)
{
  for(int i = 0; i<ms;i++)
  __delay_cycles(1000);
}

//******Ham adc**************************
unsigned int ReadADC10(int chanel)
{
  ADC10CTL0 &=~ ENC;
  ADC10CTL0 = SREF_1 + ADC10SHT_2 + ADC10ON + REF2_5V + REFON;
  ADC10AE0 |= (BIT0<<chanel);
  ADC10CTL1 |= (chanel*0x1000u);
  __delay_cycles(3000);
  ADC10CTL0 |= ENC + ADC10SC;
  while(!(ADC10CTL0 & ADC10IFG));
  ADC10CTL0 = 0;// ADC10CTL0 &=~ ADC10ON;
  return ADC10MEM;
}
//+++++++++++++++++++++++++++++++++++
#pragma vector = PORT1_VECTOR
__interrupt void PORT1 (void)
{
        counter++;// tang counter len 1 don vi
        P1IFG &= ~BIT3;// xoa co ngat
}
// chuong trinh con phuc vu ngat
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer0(void){
  
  timer++;// tang bien timer len 1 don vi
  if(timer == 135)
  {
    tocdo = counter;// gan tocdo = counter
    counter = 0;// counter = 0;
    timer = 0;// timer = 0;
}
}
