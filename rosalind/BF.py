import sys
from common import readEdgeList

def bellmanFord(graph, source):
    weight = [sys.maxint  for i in range(0,graph['numV'])]
    weight[source] = 0
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

if __name__ == '__main__':
    graph = readEdgeList(sys.argv[1], directed=True, weighted=True)
    shortest = bellmanFord(graph, 0)
    for s in shortest:
        if s == sys.maxint:
            print 'x',
        else:
            print s,
    print
