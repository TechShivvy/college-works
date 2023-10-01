def dls(graph, start, limit,level,visited=[]):
	if level<limit:	
		if start not in visited:
			visited.append(start)
			for neighbour in graph[start]:
				dls(graph,neighbour,limit,level+1,visited)
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
	print(dls(graph,"start",3,1))
		
if __name__=="__main__":
	main()
