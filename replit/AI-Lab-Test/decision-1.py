import math

class tree:
  def __init__(self,data):
    self.data = data
    self.children = []

def list_to_freqhist(list):
  freqhist = {}
  for item in list:
    if item in freqhist:
      freqhist[item] += 1
    else:
      freqhist[item] = 1
  return freqhist

def histlength(freqhist):
  sum = 0
  for key in freqhist:
    sum += freqhist[key]
  return sum

def indentation(level):
  print(6*" "*level, end=" ")

table = {
  "deadline": ["urgent", "urgent","near","none","none","none","near","near","near","urgent"],
  "isparty":["yes","no","yes","yes","no","yes","no","no","yes","no"],
  "lazy":["yes","yes","yes","no","yes","no","no","yes","yes","no"],
  "activity":["party","study","party","party","pub","party","study","tv","party","study"]
}
classified_set = ["activity"]

def split(table,attr,val):
  index = []
  subtable = table.copy()
  for i in range(len(table[attr])):
    if table[attr][i] == val:
      index.append(i)
  for subatr in subtable:
    subtable[subatr] = []
    for i in index:
      subtable[subatr].append(table[subatr][i]) 
  return subtable

def ishomogeneous(table):
  out = table[list(table)[-1]]
  s = [*set(out)]
  if(len(s) == 1):
        return True
  return False

def get_entropy(table):
  attribute = list(table)[-1]
  dict = list_to_freqhist(table[attribute])
  entropy = 0
  sum = histlength(dict)
  for key in dict:
    prob = dict[key]/sum
    term = prob*math.log2(prob)
    entropy -= term
  return entropy

def info_gain(table,subatr):
  attr = list(table)[-1]
  gain = get_entropy(table)
  dict = list_to_freqhist(table[subatr])
  sum = histlength(dict)
  for key in dict:
    prob = -dict[key]/sum
    atrlist = []
    for i in range(len(table[attr])):
      if(table[subatr][i] == key):
        atrlist.append(table[attr][i])
    atrdict = list_to_freqhist(atrlist)
    atrdsum = histlength(atrdict)
    entropy = 0
    for atrkey in atrdict:
      aprob = atrdict[atrkey]/atrdsum
      term = aprob*math.log2(aprob)
      entropy -= term
    prob *= entropy
    gain += prob
  return gain

def growtree(table):
  attribute = list(table)[-1]
  if(ishomogeneous(table)):
    indentation(len(classified_set) - 1)
    print((table[attribute][0], len(table[attribute])))
    Tree = tree(table[attribute][0])
    Tree.children = []
    return Tree
  max = 0
  maxgain = ''
  for key in table:
    if key not in classified_set:
      gain = info_gain(table,key)
      if(gain > max):
        max = gain
        maxgain = key
  classified_set.append(maxgain)
  gaindict = list_to_freqhist(table[maxgain])
  Tree = tree(maxgain)
  indentation(len(classified_set) - 1)
  print("[" + maxgain + "] :-")
  for ele in gaindict:
    indentation(len(classified_set) - 1)
    print("If {maxgain} = {ele}:-".format(maxgain=maxgain,ele=ele))
    subtable = split(table,maxgain,ele)
    Tree.children.append((growtree(subtable)))
  return Tree

def printtree(Tree):
  if Tree.children:
    print(Tree.data, end=" ")
    print("[",end='')
    for each in Tree.children:
      printtree(each)
    print("]",end='')
  else:
    print((Tree.data,), end=" ")

def main():
  print(table)
  print()
  Tree = growtree(table)
  print()
if __name__ == "__main__":
  main()