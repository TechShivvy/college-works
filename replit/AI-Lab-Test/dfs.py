def dfs(graph, start, visited=[],level=0):
	if start not in visited:
		visited.append(start)
		for neighbour in graph[start]:
			dfs(graph,neighbour,visited,level+1)
	return visited	
	
def main():
	graph ={"start":["d","e","p"],
		"d":["b","c","e"],
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
	print(dfs(graph,"start"))
		
if __name__=="__main__":
	main()
