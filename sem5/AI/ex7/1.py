
def jpdf(s,w):
	print("\nS="+str(s))
	print("W="+str(w))
	print("\n\nJPDT:\n")
	print("S/W\tW=T\tW=F\tSum")
	rSum=[0,0,0]
	cSum=[0,0]
	x=0
	for i in s:
		rSum[x]=s[i]*w['True'] + s[i]*w['False']
		print(i+"\t"+str(s[i]*w['True'])+'\t'+str(round(s[i]*w['False'],2))+'\t'+str
	(round(rSum[x],2)))
		x+=1
		cSum[0]+=s[i]*w['True']
		cSum[1]+=s[i]*w['False']
	print("Sum"+"\t"+str(cSum[0])+"\t"+str(cSum[1])+'\t'+str(cSum[0]+cSum[1])+"\n")

def prob(statement):
	l1 = statement.split(' & ')
	l2 = statement.split(' | ')
	if len(l1) > 1:
		if (l1[0].split('='))[0] == 's':
			return s[(l1[0].split('='))[-1]] * w[(l1[-1].split('='))[-1]]
		if (l1[0].split('='))[0] == 'w':
			return w[(l1[0].split('='))[-1]] * s[(l1[-1].split('='))[-1]]
	else:	
		if (l2[0].split('='))[0] == 's':
			return s[(l2[0].split('='))[-1]]
		if (l2[0].split('='))[0] == 'w':
			return w[(l2[0].split('='))[-1]]

if __name__=="__main__":
	s={"Sunny": 0.3,"Cloudy": 0.3,"Rain": 0.4}
	w={"True":0.3,"False":0.7}
	jpdf(s,w)
	print("P(s=Rain & w=True) =", prob('s=Rain & w=True'))
	print("P(s=Rain) =", prob('s=Rain'))
	print("P(w=True) =", prob('w=True'))
	print("P(s=Rain | w=True) =", prob('s=Rain | w=True'),"\n")
