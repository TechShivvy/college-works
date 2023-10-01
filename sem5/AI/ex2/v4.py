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

def dls(node,level,lvl):
	if level<lvl:
		print(list(node))	
		if list(node)==goal:
			print("Found at Level:",level)
			return True
		for neighbour in Tree[node]:
			if dls(tuple(neighbour),level+1,lvl):			
				return True
	return False

def ids(node,lvl):
	for i in range(1,lvl+1):
		print("Lvl limit: "+str(i-1))
		if dls(node,0,i):
			return True
		print()
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
lvl=3																											
#print(Tree)
print("DLS:")
if not dls((),0,lvl):
	print("Not Found")
print()
print("IDS:")
if not ids((),2):
	print("Not Found")

