#include "mbed.h"

AnalogOut Aout(D7);
AnalogIn Ain(A0);
int main(){
  while(1){
    Aout = Ain;
  }
}