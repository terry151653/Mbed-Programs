#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2);

int main() {
	printf("uLCD printing...\n");
	
    uLCD.background_color(WHITE);
    uLCD.cls();
	uLCD.color(BLUE);
    
	uLCD.printf("\n109061215\n");
    uLCD.background_color(WHITE);
	ThisThread::sleep_for(1s);

	uLCD.color(GREEN);
	uLCD.printf("Counting down:\n");
    uLCD.background_color(WHITE);
	uLCD.text_width(4); // 4X size text
	uLCD.text_height(4);
	
	for (int i = 30; i >= 0; --i)
	{
	  	uLCD.locate(1, 2);
	  	uLCD.printf("%2d", i);
        uLCD.background_color(WHITE);
	  	ThisThread::sleep_for(1s);
	}
	printf("Done.\n");
    while (1)
    {
        printf("Done.\n");
        ThisThread::sleep_for(1s);
    }
}