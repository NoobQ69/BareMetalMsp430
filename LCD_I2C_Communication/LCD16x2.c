#include "LCD16x2.h"

void lcd_send_cmd (unsigned char cmd)
{
  unsigned char data_t[4];
  unsigned char data_u, data_l;
  data_u = (cmd&0xf0);
  data_l = ((cmd<<4)&0xf0);
  
  data_t[0] = data_u|0x0C;  //en=1, rs=0
  data_t[1] = data_u|0x08;  //en=0, rs=0
  data_t[2] = data_l|0x0C;  //en=1, rs=0
  data_t[3] = data_l|0x08;  //en=0, rs=0
  I2C_MasterTransmitData(data_t, 4);
}

void lcd_send_data (unsigned char data)
{
  unsigned char data_t[4];
  char data_u, data_l;
  data_u = (data&0xf0);
  data_l = ((data<<4)&0xf0);
  data_t[0] = data_u|0x0D;  //en=1, rs=1
  data_t[1] = data_u|0x09;  //en=0, rs=1
  data_t[2] = data_l|0x0D;  //en=1, rs=1
  data_t[3] = data_l|0x09;  //en=0, rs=1
  I2C_MasterTransmitData(data_t, 4);
}

void lcd_gotoxy(unsigned char row, unsigned char column)
{
    char position;

    if (row < 2)
    {
        position = 0x80 | (row << 6);

        if (column < 16)
        {
            position = position + column;

            lcd_send_cmd(position);
            delayMs(2);
        }
    }
}

void lcd_send_string (char *str)
{
  while (*str) lcd_send_data (*str++);
  delayMs(2);
}

void lcd_reset()
{
  lcd_send_cmd(0x01);
  delayMs(10);
}

void lcd_init (void)
{
    // 4 bit initialisation
    delayMs(50);  // wait for >40ms
    lcd_send_cmd (0x30);
    delayMs(5);  // wait for >4.1ms
    lcd_send_cmd (0x30);
    delayMs(2);  // wait for >100us
    lcd_send_cmd (0x30);
    delayMs(10);
    lcd_send_cmd (0x20);  // 4bit mode
    delayMs(10);

    // dislay initialisation
    lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
    delayMs(2);
    lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
    delayMs(2);
    lcd_send_cmd (0x01);  // clear display
    delayMs(2);
    lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
    delayMs(2);
    lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}
