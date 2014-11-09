import sys
from common import readEdgeListFromFp

def bellmanFord(graph):
    weight = [0  for i in range(0,graph['numV'])]
    for i in range(1,graph['numV']):
        for e in graph['edges']:
            (u, v, w) = e
            u -= 1
            v -= 1
            cost = sys.maxint
            if weight[u] != sys.maxint:
                cost = weight[u] + w
            if cost < weight[v]:
                weight[v] = cost
    return weight

def nwc(graph):
    weight = bellmanFord(graph)
    for e in graph['edges']:
        (u, v, w) = e
        u -= 1
        v -= 1
        if (weight[u] + w) < weight[v]:
            return True
    return False

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    numGraphs = int(fp.readline())
    graphs = []
    for i in range(0,numGraphs):
        g = readEdgeListFromFp(fp, directed=True, weighted=True)
        graphs.append(g)
    fp.close()
    for g in graphs:
        if nwc(g):
            print 1,
        else:
            print -1,
