import numpy as np
import matplotlib.pyplot as plt
import random

import numpy as np

def split(matrix):
  row, col = matrix.shape
  row2, col2 = row//2, col//2
  return matrix[:row2, :col2], matrix[:row2, col2:], matrix[row2:, :col2], matrix[row2:, col2:]

def strassen(x, y):
  global count1
  count1=count1+1
  if len(x)==1:
    return x * y
  a, b, c, d = split(x)
  e, f, g, h = split(y)

  p1 = strassen(a, f - h)
  p2 = strassen(a + b, h)
  p3 = strassen(c + d, e)
  p4 = strassen(d, g - e)
  p5 = strassen(a + d, e + h)
  p6 = strassen(b - d, g + h)
  p7 = strassen(a - c, e + f)

  c11 = p5 + p4 - p2 + p6
  c12 = p1 + p2
  c21 = p3 + p4
  c22 = p1 + p5 - p3 - p7

  c = np.vstack((np.hstack((c11, c12)), np.hstack((c21, c22))))

  return c

def normal(x,y):
  global count2
  count2=count2+1
  if len(x) == 1:
    return x * y
  a, b, c, d = split(x)
  e, f, g, h = split(y)

  p1 = normal(a,e)
  p2 = normal(b,g)
  p3 = normal(a,f)
  p4 = normal(b,h)
  p5 = normal(c,e)
  p6 = normal(d,g)
  p7 = normal(c,f)
  p8 = normal(d,h)

  c11 = p1+p2
  c12 = p3+p4
  c21 = p5+p6
  c22 = p7+p8

  c = np.vstack((np.hstack((c11, c12)), np.hstack((c21, c22))))

  return c

y1=[]
y2=[]
x=[]
for i in range(2,5):
  count1=0
  count2=0
  a = np.random.randint(20, size=(2**i,2**i))
  b=np.random.randint(20,size=(2**i,2**i))
  x.append(2**i)
  c1=strassen(a,b)
  d1=normal(a,b)
  y1.append(count1)
  y2.append(count2)
x=np.array(x)
y1=np.array(y1)
y2=np.array(y2)
plt.plot(x,y1,color="green",label="Strassen")
plt.plot(x,y2,color="blue",label="normal")
plt.legend()
plt.show()
