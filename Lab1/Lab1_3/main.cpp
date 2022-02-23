/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     1000ms


int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);

    for(int i=0; i<10; i++){
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
        printf("%1.5f\n", 3.14159);
    }
}