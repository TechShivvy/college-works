#shiv

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

def dls(node,level,limit):
	if level<limit:
		print(list(node))	
		if list(node)==goal:
			print("Found at Level:",level)
			return True
		for neighbour in Tree[node]:
			if dls(tuple(neighbour),level+1,limit):			
				return True
	return False

A=[1,2,3]
tree=[([],[])]
Tree={():[]}
flag=0
for node in tree:
	a=list(node[0])							
	while not len(a)==len(A):
		#diff=sorted(list(set(A).symmetric_difference(set(a))))
		ele=mex(a)	#ele=[diff[0]]
		a+=ele
		child=node[0]+ele
		tree.append((child,[]))
		node[1].append(child)

#print(tree)
printTree()

for (key, value) in tree:
	Tree[tuple(key)]=value

goal=[2,3,1]
limit=3																											
#print(Tree)
if not dls((),0,limit):
	print("Not Found")

