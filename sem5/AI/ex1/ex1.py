from binarytree import build
def bfs():
	print("BFS:",end=" ")
	n=len(tree)
	q=[0]
	while len(q):
		i=q.pop(0)
		print(tree[i],end=" ")
		if 2*i+1<n:
			q.append(2*i+1)
		if 2*i+2<n:
			q.append(2*i+2)
	print()

def dfs(i):
	print(tree[i],end=" ")
	if 2*i+1<n:
		dfs(2*i+1)
	if 2*i+2<n:
		dfs(2*i+2)
		
color=input("Enter color: ").lower()
if color!="blue" and color!="red" :
	exit(0)
N=int(input("Enter n: "))
tree = [x for x in range(2-(len(color)&1),N+1,2)]
print(tree)
Tree=build(tree)
print(Tree)
n=N//2
if color=="red" and N&1:
	n+=1
bfs()
print("DFS:",end=" ")
dfs(0)
print()
