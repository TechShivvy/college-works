def path_f_cost(path):
	g_cost=0
	for (node,cost) in path:
		g_cost+=cost
	last_node=path[-1][0]
	H_table={'a':10,'b':8,'c':5,'d':7,'e':3,'f':6,'g':5,'h':3,'i':1,'j':0}
	h_cost=H_table[last_node]
	f_cost=g_cost+h_cost
	return f_cost,last_node
	
def astar(graph,start,goal):
	visited=[]
	queue=[[(start,0)]]
	while queue:
		queue.sort(key=path_f_cost)
		path=queue.pop(0)
		node=path[-1][0]
		
		if node in visited:
			continue
		visited.append(node)
		if node == goal:
			return path
		else:
			adj_nodes=graph.get(node,[])
			for (node2,cost) in adj_nodes:
				queue.append(path+[(node2,cost)])

if __name__=="__main__":
	graph={	'a':[('b',6),('f',3)],
		'b':[('d',2),('a',6),('c',3)],
		'c':[('b',3),('d',1),('e',5)],
		'd':[('b',2),('c',1),('e',8)],
		'e':[('c',5),('d',8),('i',5),('j',5)],
		'f':[('g',1),('h',7)],
		'g':[('f',1),('i',3)],
		'h':[('f',7),('i',2)],
		'i':[('e',5),('g',3),('h',2),('j',3)],
		'j':[('e',5),('i',3)]
		}
	print(astar(graph,'a','j'))
		
