#include "LCD.h"

int main() {
	LCD_init();          // call the initialise function
	display_to_LCD('1'); // ‘H’
	display_to_LCD('0'); // ‘E’
	display_to_LCD('9'); // ‘L’
	display_to_LCD('0'); // ‘L’
	display_to_LCD('6'); // ‘O’
	display_to_LCD('1');
	display_to_LCD('2');
	display_to_LCD('1');
	display_to_LCD('5');
	for (int x = 30; x > -1; --x)
	{
		set_location(10);
		display_to_LCD(x / 10 + '0'); // display numbers 0-9
		display_to_LCD(x % 10 + '0');
        rtos::ThisThread::sleep_for(1s);
	}
}