#include "mbed.h"


DigitalOut led1(LED1);
InterruptIn sw2(BUTTON1);
EventQueue queue(32 * EVENTS_EVENT_SIZE);

Thread t;

void led1_info() {
   // Note that printf is deferred with a call in the queue
   // It is not executed in the interrupt context
   printf("led1 is triggered! \r\n");
}

void Trig_led1()  {
   // Execute the time critical part first
   led1 = !led1;

   // Ask the queue to schedule led1_info() immediately
   queue.call(led1_info);
}

int main() {
   // callback() is used to wrap a API call to a queue object.
   // So, t will call queue.dispatch_forever(),
   // and it will start and run the queue scheduler of the EventQueue
   t.start(callback(&queue, &EventQueue::dispatch_forever));

   // 'Trig_led1' will execute in IRQ context
   sw2.rise(Trig_led1);
}