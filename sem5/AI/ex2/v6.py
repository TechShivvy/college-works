#shiv

def formTree(values, temp_array=[], root=tuple([])):
    if len(values) == 0:
            Tree[root] = []
    for i in values:
        temp_array.append(i)
        if root in Tree.keys():
            Tree[root].append(temp_array.copy())
        else:
            Tree[root] = [temp_array.copy()]

        formTree([x for x in values if x != i],
                temp_array.copy(), tuple(temp_array.copy()))
        temp_array.pop()

def printTree():
	print("\nParent\t \tChildren\n")
	for node in Tree.keys():
		print(node,"\t:\t",end="")
		print(*Tree[node], sep=', ')
		print()

def dls(node,level,lvl):
	if level<lvl:
		print(list(node), end=' ')	
		if list(node)==goal:
			print("\nFound at Level:",level)
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
		else:
			print("\nNot Found\n")
	return False

#A=[1,2,3]
print("Enter values for the tree : ",end='')
A = list(map(int, input().split()))

Tree=dict()
formTree(A)

test_dict_list = sorted(list(Tree.items()), key = lambda key : len(key[0]))
Tree = {ele[0] : ele[1]  for ele in test_dict_list}
printTree()

#goal=[2,3,1]
#lvl=3
print("Enter element to be searched : ",end='')
goal = list(map(int, input().split()))
print("Enter limit : ",end='')
lvl = int(input())

print("\nDLS:")
if not dls((),0,lvl):
	print("\nNot Found")
	
print()

print("IDS:")
ids((),lvl)




