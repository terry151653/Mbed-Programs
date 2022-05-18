#include "mbed.h"

int main() {
   BufferedSerial serdev(D1, D0, 9600);

   //Get a message from remote and resend the message to remote
   char c;
   char instr[128];
   memset(instr, '\0', 128); //clear buffer
   int i=0;
   while(true){
      serdev.read(&c, 1);
      if(c!='\r' && c!='\n'){
         printf("%c",c);
         //prepare echo back
         instr[i]=c;
         i++;
      }
      else{ //Either '\r' or '\n'
        printf("\n");
        printf("Echo back: string=%s with strlen=%d.\n", instr, strlen(instr));
        //Echo back when eol
        instr[i]='\n';
        i++;
        serdev.write(instr, strlen(instr));
        ThisThread::sleep_for(1ms);
        i=0;
        memset(instr, '\0', 128);
      }
   }
}