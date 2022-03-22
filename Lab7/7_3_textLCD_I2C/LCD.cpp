#include "LCD.h"

I2C _i2c(D14, D15);
char _slaveAddress = 0x4E;
char _lcd_bus;

void display_to_LCD(int value)
{
      _lcd_bus |= LCD_BUS_I2C_RS; // Set RS bit
      _i2c.write(_slaveAddress, &_lcd_bus, 1);
      ThisThread::sleep_for(1ms / 1000);
      _writeByte(value);
      ThisThread::sleep_for(40ms / 1000);
}

//initialise LCD function
void LCD_init(void)
{
      _i2c.frequency(100000);
      ThisThread::sleep_for(20ms);

      _writeCommand(0x02);
      // Controller is now in 4-bit mode

      _writeCommand(0x28); // Function set 001 DL N F - -
                           //  DL(Data Length)=0 (4 bits bus)
                           //  N=1 (2 lines)
                           //  F=0 (5x7 dots font, only option for 2 line display)
                           //  -  (Don't care)

      ThisThread::sleep_for(10ms);

      // display mode
      _writeCommand(0x0F); // display on, cursor on,  blink on  ; Display Ctrl 0000 1 D C B

      _writeCommand(0x01); // cls, and set cursor to 0
      ThisThread::sleep_for(20ms);

      // _writeCommand(0x80);

      //set cursor blink (0x1)
      // _writeCommand(0x0D);

      // set backlight
      // _lcd_bus |= LCD_BUS_I2C_BL;
      // _i2c.write(_slaveAddress, &_lcd_bus, 1);
}

void _setDataBits(int value)
{

      //Clear all databits
      _lcd_bus &= ~LCD_BUS_I2C_MSK;

      // Set bit by bit to support any mapping of expander portpins to LCD pins
      if (value & 0x01) {     _lcd_bus |= LCD_BUS_I2C_D4;   } // Set Databit

      if (value & 0x02) {     _lcd_bus |= LCD_BUS_I2C_D5;   } // Set Databit

      if (value & 0x04) {     _lcd_bus |= LCD_BUS_I2C_D6;   } // Set Databit

      if (value & 0x08) {     _lcd_bus |= LCD_BUS_I2C_D7;   } // Set Databit
}

void _writeByte(int value)
{
      char data[4];
      _lcd_bus |= LCD_BUS_I2C_E; // Set E bit
      _setDataBits(value >> 4);  // set data high
      data[0] = _lcd_bus;

      _lcd_bus &= ~LCD_BUS_I2C_E; // clear E
      data[1] = _lcd_bus;

      _lcd_bus |= LCD_BUS_I2C_E; // Set E bit
      _setDataBits(value);       // set data low
      data[2] = _lcd_bus;

      _lcd_bus &= ~LCD_BUS_I2C_E; // clear E
      data[3] = _lcd_bus;

      // write the packed data to the I2C portexpander
      _i2c.write(_slaveAddress, data, 4);
}

void _writeCommand(int command)
{
      _lcd_bus &= ~LCD_BUS_I2C_RS; // Reset RS bit
      _i2c.write(_slaveAddress, &_lcd_bus, 1);
      ThisThread::sleep_for(1ms / 1000);
      _writeByte(command);
      ThisThread::sleep_for(40ms / 1000); // most instructions take 40us
}