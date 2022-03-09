#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2);

int main() {
  printf("uLCD printing...\n");
  uLCD.color(WHITE);
  uLCD.printf("\nHello uLCD World\n");
  ThisThread::sleep_for(1s);
  uLCD.printf("Counting down:\n");
  uLCD.text_width(4); // 4X size text
  uLCD.text_height(4);
  uLCD.color(RED);
  for (int i = 10; i >= 0; --i) {
    uLCD.locate(1, 2);
    uLCD.printf("%2d", i);
    ThisThread::sleep_for(1000ms);
  }
  printf("Done.\n");
}