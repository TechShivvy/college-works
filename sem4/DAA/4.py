import matplotlib.pyplot as plt
def fun(n,c):
	if n==0:
		return c
	else:
		i=1
		while i<=n:
			c+=1
			i*=2
		c=fun(n-1,c)
		return fun(n-1,c)

x=[]
y=[]
for i in range(1,10):
	c=0
	x.append(i)
	c=fun(i,c)
	y.append(c)
plt.title("T(n) = 2T(n-1) + log(n)")
plt.plot(x,y)
plt.xlabel("n")
plt.ylabel("no.of steps")
plt.show()