
def selectionsort(arr):
	n=len(arr)
	
	for i in range(n):
		min_idx=i
		for j in range(i+1,n):
			if arr[j]<arr[min_idx]:
				min_idx=j
		arr[i],arr[min_idx]=arr[min_idx],arr[i]






arr=[12,43,24,35,0,-1,4,3]

selectionsort(arr)

print("Sorted Array is: ",arr)
