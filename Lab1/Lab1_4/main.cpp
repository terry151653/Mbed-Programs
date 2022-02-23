#include "mbed.h"

#define BLINKING_RATE     500ms

// main() runs in its own thread in the OS
int main()
{
    DigitalOut led1(LED1);
    DigitalOut led3(LED3);

    while (true)
    {
        for(int i = 0; i < 6; i++)
        {
            led3 = !led3;
            ThisThread::sleep_for(BLINKING_RATE);
        }
        for (int i = 0; i < 4; i++)
        {
            led1 = !led1;
            ThisThread::sleep_for(BLINKING_RATE);
        }  
    }
    
}
