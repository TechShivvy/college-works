#PART B
def expression(rv, exp):
  if len(network[rv]) == 0:
    return 'P(' + rv + ')'
  else:
    cond = ''
    cond += network[rv][0]
    for i in range(1, len(network[rv])):
      cond += ',' + network[rv][i]
    exp += 'P(' + rv + '|' + cond + ')'
    for v in network[rv]:
      exp += expression(v, exp)
  return exp

#PART B
def total_exp(network, cond_pr, exp):
  for k in network:
    if len(network[k]) == 0:
      cond_pr[k] = 'P(' + k + ')'
    else:
      cond = ''
      cond += network[k][0]
      for i in range(1, len(network[k])):
        cond += ',' + network[k][i]
      cond_pr[k] = 'P(' + k + '|' + cond + ')'
    exp += cond_pr[k]
  return exp

#PART C
def ind_param(network, cond_pr, total):
  for k in network:
    param = int(2 ** len(network[k]))
    print(cond_pr[k] + '\t\t\t\t\t' + str(param))
    total += param
  return total

#PART D
def no_con_ind_param(network):
  no = len(network)
  print("\nNumber of independent parameters if there is no conditional independence \n= " + "2^" + str(no) + ' - 1 = ' + str((2**no-1)))

#PART E (parent, children and child's parents )
def markov_blanket(network, rv, markov):
  markov.append(rv)
  for v in network[rv]:
    if v not in markov:
      markov.append(v)

  for k in network:
    if rv in network[k]:
      if k not in markov:
        markov.append(k)
      for v in network[k]:
        if v not in markov:
          markov.append(v)
  
#PART A
network = {'D1':[], 'D2':[], 'D3':[], 'S1':['D1'], 'S2':['D1', 'D2'], 'S3':['D1', 'D3'], 'S4':['D3']}

print('Conditional Probabilities :-')
for k in network:
  print(k + ': ' + expression(k, ''))

cond_pr = {}
print('\nOverall expression :-\n' + total_exp(network, cond_pr, ''))

print('\nCPT\t\t\t\tNumber of Independent Parameters')
total = ind_param(network, cond_pr, 0)
print('Total\t\t\t\t' + str(total))

no_con_ind_param(network)

print('\nMarkov Blanket :-')
for k in network:  
  markov = []
  markov_blanket(network, k, markov)
  print(k + ': ' + str(markov))
