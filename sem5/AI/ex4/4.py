import random

def collision(queens,n):
        col=0
        for i in range(n):
            for j in range(n):
                if i!=j and queens[i]==queens[j]:
                    col+=1
                if i!=j and abs(queens[i]-queens[j])==abs(i-j):
                    col+=1               
        return col

def hill_climbing(queens,n,h):
        minh=999
        dup=queens[:]
        for i in range(n):
            ind=[]
            while len(ind)!=n:
                queens[i]=(queens[i]+1)%n
                ind.append(queens[i])
                col=collision(queens,n)
                if minh>col:
                    minh=col
                    r=queens[i]
                    c=i
            queens=dup[:]
        return (minh,r,c)

def main():
	n=4
	queens=random.sample(range(0, n), n)
	h=collision(queens,n)
	print(queens) 
	print(h)
	print()
	#cnt=0
	while len(queens)!=len(set(queens)) or collision(queens,n)!=0:
	    flag=0
	    #cnt+=1
	    print("B4 : ",queens)
	    (minh,r,c)=hill_climbing(queens,n,h)
	    if h>minh:
	    	h=minh
	    	flag=1
	    	queens[c]=r
	    	print("Y: ",queens)
	    if flag==0:
	    	queens=random.sample(range(0,n),n)
	    	h=collision(queens,n)
	    	#print("----------------")
	    	print("N: ",queens)
	    #print(cnt," - ",h," - ",minh)
	    print()
	print()
	print(queens)

if __name__ == "__main__":
    main()

