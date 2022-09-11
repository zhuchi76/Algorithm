# -*- coding: utf-8 -*-
"""HW1.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1K9Afsh3_m9KdyZJcuRWdkmbOd3ZaZ-kM
"""

import matplotlib.pyplot as plt
import numpy as np

# Insertion sort
x1 = [] # size
y1 = [] # runtime (ms)

path = 'HW1_out1.txt'
#path = '/content/drive/MyDrive/Algorithm/Hw1/HW1_out1.txt'
f = open(path, 'r')
for line in f.readlines():
  temp = line.split()
  x1.append(int(temp[0]))
  y1.append(int(temp[1]))
f.close()
plt.plot(x1,y1,color='red',label='Insertion sort')


# Merge sort
x2 = [] # size
y2 = [] # runtime (ms)
path = 'HW1_out2.txt'
#path = '/content/drive/MyDrive/Algorithm/Hw1/HW1_out2.txt'
f = open(path, 'r')
for line in f.readlines():
  temp = line.split()
  x2.append(int(temp[0]))
  y2.append(int(temp[1]))
f.close()
plt.plot(x2,y2,color='blue',label='Merge sort')


plt.xlabel('Input Size')
plt.ylabel('Runtime (ms)')
plt.title('Compare Insertion sort and Merge sort runtime')
#plt.legend()
plt.show()


# Merge sort
x2_2 = [] # size
y2_2 = [] # runtime (ms)
path = 'HW1_out2_test.txt'
#path = '/content/drive/MyDrive/Algorithm/Hw1/HW1_out2_test.txt'
f = open(path, 'r')
for line in f.readlines():
  temp = line.split()
  x2_2.append(int(temp[0]))
  y2_2.append(int(temp[1]))
f.close()
plt.plot(x2_2,y2_2,color='blue',label='Merge sort')

plt.xlabel('Input Size')
plt.ylabel('Runtime (ms)')
plt.title('Zoom out Merge sort runtime')
#plt.legend()
plt.show()