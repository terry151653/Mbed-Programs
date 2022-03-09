#include "mbed.h"

void Led(DigitalOut &ledpin)
{
   for (int i = 0; i < 10; ++i)
   {                     //blink for 10 times
      ledpin = !ledpin; // toggle led
      ThisThread::sleep_for(100ms);
   }
}