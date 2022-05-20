#include "mbed.h"
#include "bbcar.h"
BufferedSerial pc(USBTX, USBRX);

Ticker servo_ticker;
Ticker encoder_ticker;
PwmOut pin5(D12), pin6(D13);
DigitalIn encoder(D10);
volatile int steps;
volatile int last;
BusInOut pattern(D4, D5, D6, D7);

BBCar car(pin5, pin6, servo_ticker);
void encoder_control()
{
    int value = encoder;
    if (!last && value)
        steps++;
    last = value;
}

int main()
{
    pc.set_baud(9600);
    encoder_ticker.attach(&encoder_control, 1ms);
    steps = 0;
    last = 0;
    car.goStraight(15);
    while (steps * 6.5 * 3.14 / 32 < 30)
    {
        // printf("encoder = %d\r\n", steps);
        ThisThread::sleep_for(100ms);
        pattern.output();
        pattern = 0b1111; wait_us(230);
        pattern.input(); wait_us(230);
        switch (pattern)
        {
            case 0b1000: car.turn(15, 0.1); printf("1\n"); break;
            case 0b1100: car.turn(15, 0.3); printf("2\n");break;
            case 0b0100: car.turn(15, 0.6); printf("3\n");break;
            case 0b0110: car.goStraight(15); printf("4\n");break;
            case 0b0010: car.turn(15, -0.6); printf("5\n");break;
            case 0b0011: car.turn(15, -0.3); printf("6\n");break;
            case 0b0001: car.turn(15, -0.1); printf("7\n");break;
            case 0b0000: printf("9\n");break;
            case 0b1111: printf("10\n");break;
            default:car.goStraight(15);printf("8\n");
        }
    }
    car.stop();
}