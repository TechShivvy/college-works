import math

def minDistance(dist,visited,n):
	min=math.inf
	for v in range(n):
		if dist[v] < min and visited[v] == False:
			min = dist[v]
			min_index = v
	return min_index

def dijkstra(graph,n):
	dist=[]
	visited=[]
	path=[]
	for i in range(n):
		dist.append(math.inf)
		visited.append(False)
		path.append([])
	start=0
	dist[start]=0
	path[0].append(0)
	for j in range(n):
		u = minDistance(dist, visited,n)
		visited[u] = True
		for v in range(n):
			if (graph[u][v] > 0 and visited[v] == False and dist[v] > dist[u] + graph[u][v]):
				dist[v] = dist[u] + graph[u][v]
				for i in range(len(path[v])):
					path[v].pop()
				for i in range(len(path[u])):
					path[v].append(path[u][i])
				path[v].append(v)  
	return dist[n-1],path[n-1]

def astar(graph,n,hr):
	dist=[]
	dist1=[]
	visited=[]
	path=[]
	for i in range(n):
		dist.append(math.inf)
		dist1.append(math.inf)
		visited.append(False)
		path.append([])
	start=0
	dist[start]=0
	dist1[start]=0
	path[0].append(0)
	for j in range(n):
		u = minDistance(dist, visited,n)
		visited[u] = True
		for v in range(n):
			if (graph[u][v] > 0 and visited[v] == False and dist[v] > dist[u] + graph[u][v]+hr[v]):
				dist1[v]=dist1[u] + graph[u][v]
				dist[v] = dist[u] + graph[u][v]+hr[v]
				for i in range(len(path[v])):
					path[v].pop()
				for i in range(len(path[u])):
					path[v].append(path[u][i])
				path[v].append(v)
	return dist1[n-1],path[n-1]

graph=[	[0,2,0,4,0,0],
	[2,0,8,15,5,0],
	[0,8,0,7,8,8],
	[4,15,2,0,2,0],
	[0,5,8,2,0,11],
	[0,0,8,0,11,0] ]
hr=[0,10,16,9,9,0]
n=6

print()
print("A* :")
v,p=astar(graph,6,hr)
print("Path:-")
ch='A'
for i in range(len(p)-1):
	if(p[i]==0):
		print("S",end="")
	else:
		print(chr(ord(ch) + p[i]-1),end="")
	print("->",end="")
print("T")
print("Cost = "+ str(v) )

print()

print("Dijkstra: ")
v,p=dijkstra(graph,6)
print("Path:-")
ch='A'
for i in range(len(p)-1):
	if(p[i]==0):
		print("S",end="")
	else:
		print(chr(ord(ch) + p[i]-1),end="")
	print("->",end="")
print("T")
print("Cost = "+ str(v) )
