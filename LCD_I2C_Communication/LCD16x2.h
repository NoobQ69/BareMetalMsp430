#ifndef __LCD_16X2_H_
#define __LCD_16X2_H_
#include "main.h"

void lcd_send_cmd (unsigned char cmd);
void lcd_send_data (unsigned char data);
void lcd_gotoxy(unsigned char row, unsigned char column);
void lcd_send_string (char *str);
void lcd_init (void);

#endif