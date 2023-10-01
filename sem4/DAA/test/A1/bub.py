
def bubblesort(arr):
	n=len(arr)
	for i in range(n):
		for j in range(n-i-1):
			if arr[j]>arr[j+1]:
				arr[j],arr[j+1]=arr[j+1],arr[j]

arr=[12,43,24,35,0,-1,4,3]

bubblesort(arr)

print("Sorted array is: ",arr)
