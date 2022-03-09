#include "mbed.h"
using namespace std::chrono;

Timer debounce;                  //define debounce timer
InterruptIn button(BUTTON1); //Interrupt on digital push button input SW2
DigitalOut led1(LED1);

void toggle()
{
   if (duration_cast<milliseconds>(debounce.elapsed_time()).count() > 1000)
   {
      //only allow toggle if debounce timer has passed 1s
      led1 = !led1;
      debounce.reset(); //restart timer when the toggle is performed
   }
}
int main()
{
   debounce.start();
   button.rise(&toggle); // attach the address of the toggle
   while (1)
      ;
}