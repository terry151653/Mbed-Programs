#include "mbed.h"

DigitalIn mypin(BUTTON1);
DigitalOut myled(LED1);

int main()
{
   // check mypin object is initialized and connected to a pin
   if (mypin.is_connected())
   {
      printf("mypin is connected and initialized! \n\r");
   }

   // Optional: set mode as PullUp/PullDown/PullNone/OpenDrain
   mypin.mode(PullNone);

   // press the button and see the console / led change
   while (1)
   {
      printf("mypin has value : %d \n\r", mypin.read());
      myled = mypin; // toggle led based on value of button
      ThisThread::sleep_for(250ms);
   }
}
