import sys
from common import stripLine, generateAdjMatrix
import re

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
    pred = [-1 for i in range(0,graph['numV'])]
    pred[source] = source
    for s in stack:
        for a in graph['adj'][s]:
            (adj, w) = a
            cost = sys.maxint
            if weight[s] != sys.maxint:
                cost = weight[s] + w
            if cost < weight[adj]:
                weight[adj] = cost
                pred[adj] = s
    for i in range(0,len(weight)):
        weight[i] *= -1
    return (weight, pred)

def printPath(pred, source, dest):
    if source == dest:
        return ''
    path = printPath(pred, source, pred[dest])
    return path + str(pred[dest]) + '->'

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    source = int(fp.readline())
    dest = int(fp.readline())
    graph = {}
    graph['edges'] = []
    reg = re.compile('(\d+?)->(\d+?):(\d+)')
    verts = set()
    for line in fp.readlines():
        match = re.findall(reg, line)
        if match is None:
            continue
        (u, v, w) = (int(match[0][0]), int(match[0][1]), int(match[0][2]))
        u += 1
        v += 1
        w *= -1   # finding longest paths
        verts.add(u)
        verts.add(v)
        graph['edges'].append((u, v, w))
    fp.close()
    graph['numE'] = len(graph['edges'])
    graph['numV'] = len(verts)
    generateAdjMatrix(graph, directed=True, weighted=True)
    stack = topologicalSort(graph)
    (weight, pred) = shortestPaths(graph, stack, source)
    path = printPath(pred, source, dest)
    path += str(dest)
    print weight[dest]
    print path
