#include "mbed.h"
using namespace std::chrono;
DigitalOut led(LED3);
void blink_led()
{
    led = !led;
}

int main()
{
    Ticker ledTicker;
    ledTicker.attach(&blink_led, 500ms);

    while (1)
    {
        ThisThread::sleep_for(1s);
    }
}