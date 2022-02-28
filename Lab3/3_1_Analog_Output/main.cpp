#include "mbed.h"

AnalogOut Aout(PA_4);
int main(){
  while(1){
    Aout = 0.25;  // 0.25 * 3.3 = 0.825 v
    ThisThread::sleep_for(2s);
    Aout = 0.5;   // 0.50 * 3.3 = 1.650 v
    ThisThread::sleep_for(2s);
    Aout = 0.75;  // 0.75 * 3.3 = 2.475 v
    ThisThread::sleep_for(2s);
  }
}