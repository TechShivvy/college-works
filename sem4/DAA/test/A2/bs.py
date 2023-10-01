def bs(arr,l,r,x):
	if r<l:
		return -1	
	mid=(l+r)//2
	if arr[mid]==x:
		return mid
	elif arr[mid]>x:
		return bs(arr,l,mid-1,x)
	else:
		return bs(arr,mid+1,r,x)
	
n=int(input("Enter no of ele: "))

arr=list(map(int,input("Enter the nos: ").strip().split()))[:n]

ele=int(input("Enter ele:"))

print(bs(arr,0,n,ele))
