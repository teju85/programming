import sys
from common import readEdgeListFromFp

def dfs(graph, node, visited):
    visited[node] = 1
    for adj in graph['adj'][node]:
        if adj in visited:
            return False
        if not dfs(graph, adj, visited):
            return False
    del visited[node]
    return True

def isDAG(graph):
    finishedNodes = {}
    for node in range(0,graph['numV']):
        visited = {}
        if not dfs(graph, node, visited):
            return False
    return True

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    numGraphs = int(fp.readline())
    graphs = []
    for i in range(0,numGraphs):
        fp.readline()
        g = readEdgeListFromFp(fp, directed=True)
        graphs.append(g)
    fp.close()
    for g in graphs:
        if isDAG(g):
            print 1,
        else:
            print -1,
    print
