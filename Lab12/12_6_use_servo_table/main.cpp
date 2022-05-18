#include "mbed.h"

#define CENTER_BASE 1500

BufferedSerial pc(USBTX, USBRX);
DigitalIn encoder(D10);
PwmOut servo(D11);

Timer t;
Ticker encoder_ticker;

volatile int steps;
volatile int last;

void servo_control(double speed) {
   if (speed > 200)       speed = 200;
   else if (speed < -200) speed = -200;

   servo=(CENTER_BASE + speed)/20000.0f;
}

void encoder_control() {
   int value = encoder;
   if(!last && value) steps++;
   last = value;
}


int main() {

   pc.set_baud(9600);

   encoder_ticker.attach(&encoder_control, 100us);

   servo.period_ms(20);

   while(1) {

   //TODO: revise this value according to your result
   servo_control(43.13);

   steps = 0;
   t.reset();
   t.start();

   ThisThread::sleep_for(8000ms);

   float time = t.read();

   printf("%1.3f\r\n", (float) steps * 6.5 * 3.14 / 32 / time);

   }
}