import numpy as np
	
def split(mat):
	r,c=mat.shape
	r2,c2=r//2,c//2
	return mat[:r2,:c2],mat[:r2,c2:],mat[r2:,:c2],mat[r2:,c2:]

def strassen(x,y):
	if len(x)==1:	return x*y
	
	a,b,c,d=split(x)
	e,f,g,h=split(y)
	
	p1=strassen(a,(f-h))
	p2=strassen(h,(a+b))
	p3=strassen(e,(c+d))
	p4=strassen(d,(g-e))
	p5=strassen((a+d),(e+h))
	p6=strassen((b-d),(g+h))
	p7=strassen((a-c),(e+f))
	
	c11=p4+p5+p6-p2
	c12=p1+p2
	c21=p3+p4
	c22=p1-p3+p5-p7
	
	c=np.vstack((np.hstack((c11,c12)),np.hstack((c21,c22))))
	return c

def normal(x,y):
	if len(x) == 1:	return x * y
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

print(strassen(np.array([[1,2],[3,4]]),np.array([[1,2],[3,4]])))
print(normal(np.array([[1,2],[3,4]]),np.array([[1,2],[3,4]])))

