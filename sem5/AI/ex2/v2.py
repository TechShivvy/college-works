
A=[1,2,3]
tree=[([],[])]

def mex(arr):
	arr=set(arr)
	ans=1
	while ans in arr:
		ans+=1
	return [ans]

def printTree():
	print("\nParent\t \tChildren\n")
	for node in tree:
		print(node[0],"\t:\t",end="")
		print(*node[1], sep=', ')
		print()
		
for node in tree:
	a=list(set(node[0]+node[1]))
	while not len(a)==len(A):
		#diff=sorted(list(set(A).symmetric_difference(set(a))))
		ele=mex(a)	#ele=[diff[0]]
		a+=ele
		child=node[0]+ele
		tree.append((child,[]))
		node[1].append(child)
	
print(tree)
printTree()


