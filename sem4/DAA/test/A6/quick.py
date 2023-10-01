
def partition(arr,l,h):
	pivot=arr[h]
	i=l-1
	for j in range(l,h):
		if arr[j]<=pivot:
			i=i+1
			arr[i],arr[j]=arr[j],arr[i]
	(arr[i+1],arr[h])=(arr[h],arr[i+1])
	return i+1

def quicksort(arr,l,h):
	if l<h:
		pi=partition(arr,l,h)
		quicksort(arr,l,pi-1)
		quicksort(arr,pi+1,h)
arr=[2,4,3,5,7,1]
quicksort(arr,0,len(arr)-1)
print(arr)
