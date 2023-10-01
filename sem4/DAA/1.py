import matplotlib.pyplot as plt
def fun(n,c):
	c+=1
	if n==0:
		return c
	else:
		return fun(n-1,c)

x=[]
y=[]
for i in range(1,100):
	c=0
	x.append(i)
	c=fun(i,c)
	y.append(c)
plt.title("T(n) = T(n-1) + 1")
plt.plot(x,y)
plt.xlabel("n")
plt.ylabel("no.of steps")
plt.show()