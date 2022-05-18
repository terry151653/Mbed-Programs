import serial
import time
import sys

if len(sys.argv) < 1:
    print ("No port input specified.")
    sys.exit()

serdev = serial.Serial(sys.argv[1])

for i in range(5):
    print(f"message: {i}")
    outstr="Send message: "+str(i)+"\n" #send only one ENTER
    serdev.write(outstr.encode())
    time.sleep(0.001)
    line=serdev.readline()
    print(line)

serdev.close()