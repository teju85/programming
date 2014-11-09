import sys
from common import readEdgeList

def _dfsTopological(graph, node, visited, stack):
    visited.add(node)
    for a in graph['adj'][node]:
        (adj, w) = a
        if adj not in visited:
            _dfsTopological(graph, adj, visited, stack)
    stack.append(node)

def topologicalSort(graph):
    stack = []
    visited = set()
    for i in range(0,graph['numV']):
        if i not in visited:
            _dfsTopological(graph, i, visited, stack)
    stack.reverse()
    return stack

def shortestPaths(graph, stack, source):
    weight = [sys.maxint   for i in range(0,graph['numV'])]
    weight[source] = 0
    for s in stack:
        for a in graph['adj'][s]:
            (adj, w) = a
            cost = sys.maxint
            if weight[s] != sys.maxint:
                cost = weight[s] + w
            if cost < weight[adj]:
                weight[adj] = cost
    return weight

if __name__ == '__main__':
    graph = readEdgeList(sys.argv[1], directed=True, weighted=True)
    stack = topologicalSort(graph)
    weight = shortestPaths(graph, stack, 0)
    for w in weight:
        if w == sys.maxint:
            print 'x',
        else:
            print w,
    print ''
