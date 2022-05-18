#include "mbed.h"
#include "bbcar.h"
BufferedSerial pc(USBTX, USBRX);

Ticker servo_ticker;
Ticker encoder_ticker;
PwmOut pin5(D12), pin6(D13);
DigitalIn encoder(D10);
volatile int steps;
volatile int last;

BBCar car(pin5, pin6, servo_ticker);
void encoder_control() {
   int value = encoder;
   if (!last && value) steps++;
   last = value;
}

int main() {
   pc.set_baud(9600);
   encoder_ticker.attach(&encoder_control, 1ms);
   steps = 0;
   last = 0;
   while (1)
   {
       steps = 0;
       car.goStraight(100);
        while(steps*6.5*3.14/32 < 20)
        {
            // printf("encoder = %d\r\n", steps);
            ThisThread::sleep_for(100ms);
        }
        steps = 0;
        car.turn(50, -0.001);
        while(steps*6.5*3.14/32 < 17.29)
        {
            // printf("encoder = %d\r\n", steps);
            ThisThread::sleep_for(100ms);
        }
   }
   
}