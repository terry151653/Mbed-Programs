#include "mbed.h"

using namespace std::chrono;

Timer timer_fast, timer_slow;
DigitalOut led1(LED1);
DigitalOut led2(LED2);

int main(){
    timer_fast.start();
    timer_slow.start();

    while(1){
        if(chrono::duration_cast<chrono::seconds>(timer_fast.elapsed_time()).count() > 1){
            led1 = !led1;
            timer_fast.reset();
        }
        if(chrono::duration_cast<chrono::seconds>(timer_slow.elapsed_time()).count() > 2){
            led2 = !led2;
            timer_slow.reset();
        }
    }
}