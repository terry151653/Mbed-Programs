#ifndef LCD_H
#define LCD_H

#include "mbed.h"

void toggle_enable(void);        //function to toggle/pulse the enable bit
void LCD_init(void);             //function to initialise the LCD
void display_to_LCD(char value); //function to display characters
void set_location(char location);//function to set display location

#endif