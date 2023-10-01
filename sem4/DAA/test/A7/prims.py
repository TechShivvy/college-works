def prims(G,V):
	INF=99999
	selected=[0]*V
	selected[0]=True
	e=0
	while(e<V-1):
		x=0
		y=0
		mini=INF
		for i in range(V):
			if selected[i]:
				for j in range(V):
					if ((not selected[j] ) and G[i][j]):
						if mini>G[i][j]:
							x=i
							y=j
							mini=G[i][j]
							print(x,"-",y,":",G[i][j])
							selected[y]=True
							e+=1


G= [ [0, 2, 0, 6, 0],
            [2, 0, 3, 8, 5],
            [0, 3, 0, 0, 7],
            [6, 8, 0, 0, 9],
            [0, 5, 7, 9, 0]]
prims(G,5)
