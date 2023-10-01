import random

def heuristic(queens,n):
	col=0
	for i in range(n):
		for j in range(n):
			if i!=j and queens[i]==queens[j]:
				col+=1
			if i!=j and abs(queens[i]-queens[j])==abs(i-j):
				col+=1               
	return col

def collisions(queens,n,h):
	minh=99999
	dup=queens[:]
	for i in range(n):
		ind=[]
		while len(ind)!=n:
			queens[i]=(queens[i]+1)%n
			ind.append(queens[i])
			col=heuristic(queens,n)
			if minh>col:
				minh,r,c=col,queens[i],i
		queens=dup[:]
	return (minh,r,c)

def hill_climbing(queens,n,h):
	while len(queens)!=len(set(queens)) or h!=0:
		minh,r,c=collisions(queens,n,h)
		if h>minh:
			h,queens[c]=minh,r
		else:
			queens[random.randint(0,n-1)]=random.randint(0,n-1)
			h=heuristic(queens,n)
	return (queens,h)

def print_board(queens,n):
	print()
	for i in range(n):
		for j in range(n):
			print(" -" if queens[j]!=i else " Q",end="")
		print()
	print()

def main():
	print(" N-queens: ",end="\n\n")
	n=int(input(" Enter N: "))
	#n=8
	queens=random.sample(range(0, n), n)
	h=heuristic(queens,n)
	print("\n Initial State: ",end="\n")
	print_board(queens,n) 
	print(" Initial Collisions/Heuristic Value: ",h,end="\n")
	queens,h=hill_climbing(queens,n,h)
	print()
	print(" Final Configuration: ",end="\n")
	print_board(queens,n)
	print(" Collisions/Heuristic Value: ",h,end="\n\n")

if __name__ == "__main__":
	main()
