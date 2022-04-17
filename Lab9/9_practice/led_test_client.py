# led_test_client.py
# Test client for erpc led server example
# Author: becksteing/Jing-Jia Liou
# Date: 02/13/2022
# Blinks LEDs on a connected Mbed-enabled board running the erpc LED server example

from time import sleep
import erpc
from blink_led import *
import sys

if __name__ == "__main__":

    if len(sys.argv) != 2:
        print("Usage: python led_test_client.py <serial port to use>")
        exit()

    # Initialize all erpc infrastructure
    xport = erpc.transport.SerialTransport(sys.argv[1], 9600)
    client_mgr = erpc.client.ClientManager(xport, erpc.basic_codec.BasicCodec)
    client = client.LEDBlinkServiceClient(client_mgr)

    # Blink LEDs on the connected erpc server
    turning_on = True
    while True:
        for i in range(1, 4):
            print("Call led3_change")
            client.led3_change()
            sleep(0.5)

        turning_on = not turning_on