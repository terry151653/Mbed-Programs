import matplotlib.pyplot as plt
import numpy as np
import serial

Ts = 5;   # signal interval
end = 120; # signal end point
n = int(end/Ts)+1

x = np.linspace(0, end, num=n) # x axis
y = np.zeros(n)                # y axis

serdev = 'com7'
s = serial.Serial(serdev)

for i in range(0, n):
    line=s.readline() # Read a string from B_L4S5I_IOT01A terminated with '\n'
    print (line)
    y[i] = float(line)

plt.figure()
plt.plot(x,y)
plt.xlabel('signal')
plt.ylabel('speed (cm/sec)')
plt.show()
s.close()