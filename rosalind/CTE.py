import sys
from common import readEdgeListFromFp

def shortestPath(graph, source, root):
    frontier = {}
    path = []
    for i in range(0, graph['numV']):
        frontier[i] = 1
        path.append([sys.maxint, i])
    path[source][0] = graph['edges'][0][2]
    while len(frontier) > 0:
        shortest = sys.maxint
        node = -1
        for p in path:
            if p[1] in frontier  and  p[0] < shortest:
                (shortest, node) = p
        if node == -1:
            break
        del frontier[node]
        for tmp in graph['adj'][node]:
            (adj, weight) = tmp
            dist = path[node][0] + weight
            if path[adj][0] > dist:
                path[adj][0] = dist
    if path[root][0] == sys.maxint:
        return -1
    else:
        return path[root][0]

def shortestCycle(graph):
    edge = graph['edges'][0]
    return shortestPath(graph, edge[1]-1, edge[0]-1)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    numGraphs = int(fp.readline())
    graphs = []
    for i in range(0,numGraphs):
        g = readEdgeListFromFp(fp, directed=True, weighted=True)
        graphs.append(g)
    fp.close()
    for g in graphs:
        print shortestCycle(g),
    print
