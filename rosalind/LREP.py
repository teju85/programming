import sys
from common import stripLine, generateAdjMatrix

def readSuffixTree(fp):
    tree = {}
    tree['numV'] = 0
    tree['numE'] = 0
    tree['edges'] = []
    tree['map'] = {}
    tree['rmap'] = {}
    for line in fp.readlines():
        line = stripLine(line)
        tmp = line.split(' ')
        if tmp[0] not in tree['map']:
            tree['numV'] += 1
            tree['map'][tmp[0]] = tree['numV']
            tree['rmap'][tree['numV']] = tmp[0]
        if tmp[1] not in tree['map']:
            tree['numV'] += 1
            tree['map'][tmp[1]] = tree['numV']
            tree['rmap'][tree['numV']] = tmp[1]
        start = int(tmp[2])-1
        length = int(tmp[3])
        edge = (tree['map'][tmp[0]], tree['map'][tmp[1]], (start, length))
        tree['edges'].append(edge)
        tree['numE'] += 1
    generateAdjMatrix(tree, directed=True, weighted=True)
    return tree

# since its tree, no need for 'visited'!
def dfs(tree, node, start, length):
    if tree['deg'][node] <= 0:
        return 1
    tree['leaves'][node][1] = start
    tree['leaves'][node][2] = length
    num = 0
    for a in tree['adj'][node]:
        (adj, s) = a
        num += dfs(tree, adj, start, length+s[1])
    tree['leaves'][node][0] = num
    return num

def numLeavesRecursive(tree):
    tree['leaves'] = [[0, 0, 0]  for i in range(0,tree['numV'])]
    dfs(tree, 0, 0, 0)

def lrs(tree, s, k):
    maxLen = 0
    maxStart = -1
    le = tree['leaves']
    for node in range(1,tree['numV']):
        if le[node][0] >= k  and  le[node][2] > maxLen:
            maxLen = le[node][2]
            maxStart = le[node][1]
            print le[node]
    return s[maxStart:maxStart+maxLen]

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    s = stripLine(fp.readline())
    k = int(fp.readline())
    tree = readSuffixTree(fp)
    fp.close()
    numLeavesRecursive(tree)
    print lrs(tree, s, k)
