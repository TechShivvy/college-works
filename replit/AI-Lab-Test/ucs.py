def path_cost(path):
	total_cost=0
	for (node,cost) in path:
		total_cost+=cost
	return total_cost,path[-1][0]
	
def ucs(graph,start,goal):
	visited=[]
	queue=[[(start,0)]]
	while queue:
		queue.sort(key=path_cost)
		path=queue.pop(0)
		node=path[-1][0]
		if node in visited:
			continue
		visited.append(graph)
		if node == goal:
			return path
		else:
			adj_nodes=graph.get(node,[])
			for (node2,cost) in adj_nodes:
				queue.append(path+[(node2,cost)])

def main():
	graph ={"start":[("d",3),("e",9),("p",1)],
		"d":[("b",1),("c",8),("e",2)],
		"e":[("h",1),("r",9)],
		"p":[("q",15)],
		"b":[("a",2)],
		"c":[("a",2)],
		"h":[("p",4),("q",4)],
		"r":[("f",5)],
		"q":[("r",3)],
		"f":[("goal",5),("c",5)],
		}
	print(ucs(graph,"start","goal"))
		
if __name__=="__main__":
	main()
