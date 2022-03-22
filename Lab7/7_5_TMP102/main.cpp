#include "mbed.h"

I2C m_i2c(D14, D15);
char m_addr = 0x90;
int main()
{
   while (1)
   {
      const char tempRegAddr = 0x00;

      m_i2c.write(m_addr, &tempRegAddr, 1);
      //Set pointer to the temperature register

      char reg[2] = {0, 0};
      m_i2c.read(m_addr, reg, 2); //Read

      unsigned short res = (reg[0] << 4) | (reg[1] >> 4);
      float temp =  (float) ((float)res * 0.0625);
      printf("Temp code=(%d, %d)\r\n", reg[0], reg[1]);
      printf("Temp = %f.\r\n", temp);
      ThisThread::sleep_for(1s);
   }
}