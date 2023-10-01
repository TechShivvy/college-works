def fact(n):
	return n*fact(n-1) if n>=2 else 1
n=int(input("Enter a number: "))
print("Factorial of ",n,"is: ",fact(n))
