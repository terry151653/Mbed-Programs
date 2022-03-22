/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

DigitalOut led1(LED1);
InterruptIn sw(BUTTON1);
EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;

/*
void rise_handler(void)
{
    queue.call(printf, "rise_handler in context %p\n", ThisThread::get_id());
    // Toggle LED
    led1 = !led1;
}
*/
void rise_handler_user_context(void) {
    printf("rise_handler_user_context in context %p\r\n", ThisThread::get_id());
}

void rise_handler(void) {
    // Execute the time critical part first
    led1 = !led1;
    // The rest can execute later in user context (and can contain code that's not interrupt safe).
    // We use the 'queue.call' function to add an event (the call to 'rise_handler_user_context') to the queue.
    queue.call(rise_handler_user_context);
}

void fall_handler(void)
{
    printf("fall_handler in context %p\n", ThisThread::get_id());
    // Toggle LED
    led1 = !led1;
}

int main()
{
    // Start the event queue
    t.start(callback(&queue, &EventQueue::dispatch_forever));
    printf("Starting in context %p\r\n", ThisThread::get_id());

    // The 'rise' handler will execute in IRQ context
    sw.rise(queue.event(rise_handler));//sw.rise(rise_handler);

    // The 'fall' handler will execute in the context of thread 't'
    sw.fall(queue.event(fall_handler));
}