import matplotlib.pyplot as plt 
import numpy as np
import math

file1 = open("exponential.csv","r")
file2 = open("linear.csv","r")

x1=[]
x2=[]
y1=[]
y2=[]

while True:
    line = file1.readline()
    if not line:
        break
    pair = line.split(",")
    y = float(pair[1])
    if y>0 :
        x1 = np.append(x1,int(pair[0]))
        y1 = np.append(y1,math.log(y,2))

while True:
    line = file2.readline()
    if not line:
        break
    pair = line.split(",")
    y = float(pair[1])
    if y>0 :
        x2 = np.append(x2,int(pair[0]))        
        y2 = np.append(y2,math.log(y,2))


plt.plot(x1,y1, label = "exponential growth")
plt.plot(x2,y2, label = "linear growth")
plt.xlabel("Number of inserts (logarithmic scale) ")
plt.ylabel("Time taken (logarithmic scale) ")
plt.title("Dequeue Implementation")
plt.legend(loc='best')
plt.show()

