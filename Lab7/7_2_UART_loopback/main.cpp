#include "mbed.h"

#define MAXIMUM_BUFFER_SIZE 6

static DigitalOut led1(LED1); // led1 = PA_5
static DigitalOut led2(LED2); // led2 = PB_14

Thread thread1;
Thread thread2;

static BufferedSerial device1(D10, D9); // tx, rx  D10:tx  D9:rx
static BufferedSerial device2(D1, D0);  // tx, rx   D1:tx   D0:rx
static BufferedSerial serial_port(USBTX, USBRX);

void master_thread() {
  char buf1[MAXIMUM_BUFFER_SIZE] = {'0', '1', '2', '0', '1', '2'};
  printf("Blinking LED1 and LED2 in order twice\n");
  for (int i = 0; i < 6; i++) {
    device1.write(&buf1[i], 1);
    ThisThread::sleep_for(1s);
  }
  printf("Waiting for command from terminal. 0: turn off both. 1: turn on LED1. 2: turn on LED2.\n");
  while(1){
      if (serial_port.readable()) {
          char input;
          uint32_t num = serial_port.read(&input, 1);
          device1.write(&input, 1);
      }
  }
}

void slave_thread() {
  led1 = 0;
  led2 = 0;

  while (1) {
    char buf2[MAXIMUM_BUFFER_SIZE];
    if (device2.readable()) {
      device2.read(buf2, 1);

      if (buf2[0] == '1') {
        led1 = 1;
        led2 = 0;
      } else if (buf2[0] == '2') {
        led1 = 0;
        led2 = 1;
      } else {
        led1 = 0;
        led2 = 0;
      }
      printf("Got: %s\n", buf2);
    }
  }
}

int main() {
  // Set desired properties (9600-8-N-1).
  device1.set_baud(9600);
  device1.set_format(
      /* bits */ 8,
      /* parity */ BufferedSerial::None,
      /* stop bit */ 1);

  // Set desired properties (9600-8-N-1).
  device2.set_baud(9600);
  device2.set_format(
      /* bits */ 8,
      /* parity */ BufferedSerial::None,
      /* stop bit */ 1);

  thread1.start(master_thread);
  thread2.start(slave_thread);
}