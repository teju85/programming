import sys
from common import readEdgeList

def shortestPath(graph, source):
    frontier = {}
    path = []
    for i in range(0, graph['numV']):
        frontier[i] = 1
        path.append([sys.maxint, i])
    path[source][0] = 0  #source -> source 0 distance
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
    for i in range(0,graph['numV']):
        if path[i][0] == sys.maxint:
            path[i][0] = -1
    return path

if __name__ == '__main__':
    graph = readEdgeList(sys.argv[1], directed=True, weighted=True)
    source = 0
    arr = shortestPath(graph, source)
    for a in arr:
        print a[0],
    print
