def ids(graph,start,limit):
	for i in range(limit):
		print("level:"+str(i+1),dls(graph,start,i+1,1,[]))

def dls(graph, start, limit,level,visited=[]):
	if level<=limit:	
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
	ids(graph,"start",3)
	print()
	print(dls(graph,"start",3,1))
		
if __name__=="__main__":
	main()
