#shiv

A=[1,2,3]
Tree=dict()

def form(values, temp_array=[], root=tuple([])):
    if len(values) == 0:
        return
    for i in values:
        temp_array.append(i)
        if root in Tree.keys():
            Tree[root].append(temp_array.copy())
        else:
            Tree[root] = [temp_array.copy()]
        form([x for x in values if x != i],temp_array.copy(), tuple(temp_array.copy()))
        temp_array.pop()
        
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

form(A)
#printTree()
print(Tree)
for i in Tree.keys():
    for j in range(len(Tree[i])):
        Tree[i][j] = tuple(Tree[i][j])

goal=[2,1,3]
lvl=4																									
#print(Tree)
print("DLS:")
if not dls((),0,lvl):
	print("Not Found")
print()
print("IDS:")
if not ids((),2):
	print("Not Found")

