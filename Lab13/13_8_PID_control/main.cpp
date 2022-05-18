#include "mbed.h"
#include "bbcar.h"
#include <math.h>
#include <stdlib.h>
#include "stm32l475e_iot01_magneto.h"

#define bound 0.9
#define PI 3.14159

BufferedSerial pc(USBTX, USBRX);

Ticker servo_ticker;
PwmOut pin5(D12), pin6(D13);
BBCar car(pin5, pin6, servo_ticker);


float state[3] = {0};
float Kp = 0, Ki = 0, Kd = 0;
float a0 = 0, a1 = 0, a2 = 0;

//The formula is:
//y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]
//A0 = Kp + Ki + Kd
//A1 = (-Kp ) - (2 * Kd )
//A2 = Kd
void pid_init(){
   state[0] = 0;
   state[1] = 0;
   state[2] = 0;
   a0 = Kp + Ki + Kd;
   a1 = (-Kp) - 2*Kd;
   a2 = Kd;
}
float pid_process(float in){
   int out = in*a0 + a1*state[0] + a2*state[1] + state[2];

   //update state
   state[1] = state[0];
   state[0] = in;
   state[2] = out;

   return out;
}

int main() {
   int16_t pDataXYZ[3] = {0};
   char rotation;
   char buff[256];
   float degree, target_degree, diff;
   FILE *devin = fdopen(&pc, "r");
   FILE *devout = fdopen(&pc, "w");

   //pid control setup
   Kp = 2.0; Ki = 1.0; Kd = 0;
   pid_init();

   // acc sensor setup
   BSP_MAGNETO_Init();

   while(1) {
      ThisThread::sleep_for(100ms);
      // read wanted degree
      for( int i = 0; i < 1; i++ ) {
         rotation = fputc(fgetc(devin), devout);
      }
      for( int i = 0; i < 2; i++ ) {
         buff[i] = fputc(fgetc(devin), devout);
      }
      printf("\r\n");

      int turn = atoi(buff);

      // judge current car degree
      BSP_MAGNETO_GetXYZ(pDataXYZ);
      degree = atan2(pDataXYZ[1], pDataXYZ[0]) * 180 / PI;

      if (rotation == 'l') {
         target_degree = degree - turn;
      } else if (rotation == 'r') {
         target_degree = degree + turn;
      } else {
         target_degree = degree;
      }

      if (target_degree < -180) {
         target_degree = 360 + target_degree;
      } else if (target_degree > 180) {
         target_degree = 360 - target_degree;
      }
      diff = degree - target_degree;

      //The car will continue to turn to the target degree until the error is small enough
      while( abs(diff) > 8) {
         //Process the PID control
         float correction = pid_process(diff);
         //bound the value from -0.9 to -.9
         correction = car.clamp(correction, bound, -bound);
         float turn = (rotation == 'l') ? (1-abs(correction)) : (-1+abs(correction));
         car.turn(car.turn2speed(turn),turn);
         ThisThread::sleep_for(100ms);

         BSP_MAGNETO_GetXYZ(pDataXYZ);
         degree = atan2(pDataXYZ[1], pDataXYZ[0]) * 180 / PI;

         diff = degree - target_degree;
         printf("degree:%f, target: %f, diff:%f \r\n", degree, target_degree, diff);
      }
      car.stop();
      pid_init();
   }
}