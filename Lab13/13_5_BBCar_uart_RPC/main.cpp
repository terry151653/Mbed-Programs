#include "mbed.h"
#include "drivers/DigitalOut.h"

#include "erpc_simple_server.h"
#include "erpc_basic_codec.h"
#include "erpc_crc16.h"
#include "UARTTransport.h"
#include "DynamicMessageBufferFactory.h"
#include "bbcar_control_server.h"
// Uncomment for actual BB Car operations
#include "bbcar.h"

Ticker servo_ticker;
PwmOut pin5(D12), pin6(D13);

BBCar car(pin5, pin6, servo_ticker);


/**
 * Macros for setting console flow control.
 */
#define CONSOLE_FLOWCONTROL_RTS     1
#define CONSOLE_FLOWCONTROL_CTS     2
#define CONSOLE_FLOWCONTROL_RTSCTS  3
#define mbed_console_concat_(x) CONSOLE_FLOWCONTROL_##x
#define mbed_console_concat(x) mbed_console_concat_(x)
#define CONSOLE_FLOWCONTROL mbed_console_concat(MBED_CONF_TARGET_CONSOLE_UART_FLOW_CONTROL)

//mbed::DigitalOut led1(LED1, 1);
//mbed::DigitalOut led2(LED2, 1);
//mbed::DigitalOut led3(LED3, 1);
//mbed::DigitalOut* leds[] = { &led1, &led2, &led3 };
// Uncomment for actual BB Car operations
BBCar* cars[] = {&car}; //Control only one car

/****** erpc declarations *******/

void stop(uint8_t car){
    if(car == 1) { //there is only one car
        //*leds[car - 1] = 0;
        // Uncomment for actual BB Car operations
        (*cars[car -1]).stop();
        printf("Car %d stop.\n", car);
  }
}

void goStraight(uint8_t car, int32_t  speed){
    if(car == 1) { //there is only one car
        //*leds[car - 1] = 0;
        // Uncomment for actual BB Car operations
        (*cars[car -1]).goStraight(speed);
        printf("Car %d go straight at speed %d.\n", car, speed);
  }
}

void turn(uint8_t car, int32_t speed, double factor){
    if(car == 1) { //there is only one car
        //*leds[car - 1] = 0;
        // Uncomment for actual BB Car operations
        (*cars[car -1]).turn(speed, factor);
        printf("Car %d turn at speed %d with a factor of %f.\n", car, speed, factor);
  }
}

/** erpc infrastructure */
ep::UARTTransport uart_transport(D1, D0, 9600);
ep::DynamicMessageBufferFactory dynamic_mbf;
erpc::BasicCodecFactory basic_cf;
erpc::Crc16 crc16;
erpc::SimpleServer rpc_server;

/** LED service */
BBCarService_service car_control_service;

int main(void) {

  // Initialize the rpc server
  uart_transport.setCrc16(&crc16);

  // Set up hardware flow control, if needed
#if CONSOLE_FLOWCONTROL == CONSOLE_FLOWCONTROL_RTS
  uart_transport.set_flow_control(mbed::SerialBase::RTS, STDIO_UART_RTS, NC);
#elif CONSOLE_FLOWCONTROL == CONSOLE_FLOWCONTROL_CTS
  uart_transport.set_flow_control(mbed::SerialBase::CTS, NC, STDIO_UART_CTS);
#elif CONSOLE_FLOWCONTROL == CONSOLE_FLOWCONTROL_RTSCTS
  uart_transport.set_flow_control(mbed::SerialBase::RTSCTS, STDIO_UART_RTS, STDIO_UART_CTS);
#endif

  printf("Initializing server.\n");
  rpc_server.setTransport(&uart_transport);
  rpc_server.setCodecFactory(&basic_cf);
  rpc_server.setMessageBufferFactory(&dynamic_mbf);

  // Add the led service to the server
  printf("Adding BBCar server.\n");
  rpc_server.addService(&car_control_service);

  // Run the server. This should never exit
  printf("Running server.\n");
  rpc_server.run();
}