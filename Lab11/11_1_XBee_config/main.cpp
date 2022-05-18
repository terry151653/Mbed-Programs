#include "mbed.h"

static BufferedSerial pc(USBTX, USBRX);
static BufferedSerial xbee(D1, D0);
EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;

void pc_rx_interrupt(void);
void pc_rx(void);
void xbee_rx_interrupt(void);
void xbee_rx(void);

int main(){

   pc.set_baud(9600);
   xbee.set_baud(9600);
   printf("Begin test\r\n");
   t.start(callback(&queue, &EventQueue::dispatch_forever));

   // Setup a serial interrupt function of receiving data from pc

   pc.set_blocking(false);
   pc.sigio(queue.event(pc_rx_interrupt));

   // Setup a serial interrupt function of receiving data from xbee

   xbee.set_blocking(false);
   xbee.sigio(queue.event(xbee_rx_interrupt));

}

void pc_rx_interrupt(void){
   queue.call(&pc_rx);
}

void pc_rx(void){
   static int i = 0;
   static char str[50] = {0};
   while(pc.readable()){
      char c[1];
      pc.read(c, 1);
      if(c[0]!=0x03 && c[0]!='\n'){

         pc.write(c, 1);
         str[i] = c[0];
         i++;
         str[i] = '\r';
         str[i+1] = '\n';
         str[i+2] = '\0';

         if(strncmp(str, "+++", 3) == 0){
            xbee.write("+++", 3);
            i = 0;
         }

      }else{
         xbee.write(str, i);
         i = 0;
         printf("\r\n");
      }
   }
      ThisThread::sleep_for(1ms);
}

void xbee_rx_interrupt(void){
   queue.call(&xbee_rx);
}

void xbee_rx(void){
   while(xbee.readable()){
      char c[0];
      xbee.read(c, 1);
      if(c[0]!='\r' && c[0]!='\n'){
         printf("%c",c[0]);
      }
      else{
         printf("\r\n");
      }
   }
   ThisThread::sleep_for(1ms);
}