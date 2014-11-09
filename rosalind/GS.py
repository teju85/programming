import sys
from common import readEdgeListFromFp

def dfs(graph, node, visited):
    visited.add(node)
    for adj in graph['adj'][node]:
        if adj not in visited:
            dfs(graph, adj, visited)

def generalSink(graph):
    for node in range(0,graph['numV']):
        visited = set()
        dfs(graph, node, visited)
        if len(visited) == graph['numV']:
            return node+1
    return -1

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
        print generalSink(g),
    print
