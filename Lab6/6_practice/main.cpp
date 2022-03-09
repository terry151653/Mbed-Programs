#include "mbed.h"
using namespace std::chrono;

void blink_led2()
{
    led2 = !led2;
}

int main()
{
    Ticker ledTicker;
    ledTicker.attach(&blink_led2, 1s);

    while (1)
    {
        ThisThread::sleep_for(1s);
    }
}