#include "mbed.h"

BufferedSerial pc(USBTX, USBRX);
DigitalInOut ping(D11);
Timer t;

int main() {

   float val;
   pc.set_baud(9600);

   while(1) {

      ping.output();
      ping = 0; wait_us(200);
      ping = 1; wait_us(5);
      ping = 0; wait_us(5);

      ping.input();
      while(ping.read() == 0);
      t.start();
      while(ping.read() == 1);
      val = t.read();
      printf("Ping = %lf\r\n", val*17700.4f);
      t.stop();
      t.reset();

      ThisThread::sleep_for(1s);
   }
}