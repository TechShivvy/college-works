
A=[1,2,3]

def mex(arr):
	arr = set(arr)
	ans = 1
	while ans in arr:
		ans += 1
	return [ans]
	
'''tree=[{():[]}]
for node in tree:
	for k,v in node.items():
		child_base=list(k)
		a=list(set(child_base+v))
		while not len(a)==len(A):
			ele=		mex(a)
			a+=ele
			child=child_base+ele
			if not len(child)==len(A):
				tree.append({tuple(child):[]})
			node[k].append(child)'''

tree=[([],[])]
for node in tree:
	child_base=list(node[0])
	a=list(set(child_base+node[1]))
	while not len(a)==len(A):
		ele=mex(a)
		a+=ele
		child=child_base+ele
		if not len(child)==len(A):
			tree.append((child,[]))
		node[1].append(child)
print(tree)


