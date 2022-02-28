#include "mbed.h"

PwmOut PWM1(D6);
AnalogIn Ain(A0);
int main()
{
   while (1)
   {
      PWM1.period_ms(5);
      PWM1 = Ain;
      printf("%f\n\r", PWM1.read());
      ThisThread::sleep_for(50ms);
   }
}