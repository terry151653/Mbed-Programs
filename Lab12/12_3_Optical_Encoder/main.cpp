#include "mbed.h"

BufferedSerial pc(USBTX, USBRX);
DigitalIn encoder(D11);

Ticker encoder_ticker;

volatile int steps;
volatile int last;

void encoder_control() {
   int value = encoder;
   if (!last && value) steps++;
   last = value;
}

int main() {
   pc.set_baud(9600);
   printf("Before start\r\n");

   encoder_ticker.attach(&encoder_control, .01);

   steps = 0;
   last = 0;

   while(1) {
      ThisThread::sleep_for(2000ms);
      printf("encoder = %d\r\n", steps);
   }
}