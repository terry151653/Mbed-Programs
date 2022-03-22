#ifndef LCD_H
#define LCD_H

#include "mbed.h"


#define LCD_BUS_I2C_RS (1 << 0)
#define LCD_BUS_I2C_RW (1 << 1)
#define LCD_BUS_I2C_E  (1 << 2)
#define LCD_BUS_I2C_BL (1 << 3)
#define LCD_BUS_I2C_D4 (1 << 4)
#define LCD_BUS_I2C_D5 (1 << 5)
#define LCD_BUS_I2C_D6 (1 << 6)
#define LCD_BUS_I2C_D7 (1 << 7)
#define LCD_BUS_I2C_MSK (LCD_BUS_I2C_D4 | LCD_BUS_I2C_D5 | LCD_BUS_I2C_D6 | LCD_BUS_I2C_D7)

// void toggle_enable(void);      //function to toggle/pulse the enable bit
void LCD_init(void);             //function to initialise the LCD
void display_to_LCD(int value);  //function to display characters
void _setDataBits(int value);
void _writeByte(int value);
void _writeCommand(int);


#endif