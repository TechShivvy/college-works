import collections

def bfs(graph,root):
	visited, queue = set(), collections.deque([root])
	while queue: 
        	vertex = queue.popleft()
        	print(vertex,end=",")
        	for neighbour in graph[vertex]: 
            		if neighbour not in visited: 
                		visited.add(neighbour) 
                		queue.append(neighbour)

def main():
	graph ={"start":["d","e","p"],
		"d":["b","c"],
		"e":["h","r"],
		"p":["q"],
		"b":["a"],
		"c":["a"],
		"h":["p","q"],
		"r":["f"],
		"q":["r"],
		"a":[],
		"f":["goal","c"],
		"goal":[]
		}
	bfs(graph,"start")
		
if __name__=="__main__":
	main()
