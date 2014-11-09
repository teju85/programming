import sys
from common import readEdgeList

def shortestPath(graph, source):
    path = [-1  for i in range(0, graph['numV'])]
    path[source] = 0  #source -> source 0 distance
    frontier = []
    frontier.append(source)
    visited = set()
    visited.add(source)
    while len(frontier) > 0:
        node = frontier[0]
        del frontier[0]
        for adj in graph['adj'][node]:
            if adj not in visited:
                frontier.append(adj)
                visited.add(adj)
                path[adj] = path[node] + 1
    return path

if __name__ == '__main__':
    graph = readEdgeList(sys.argv[1], True)
    source = 0
    arr = shortestPath(graph, source)
    for a in arr:
        print a,
    print
