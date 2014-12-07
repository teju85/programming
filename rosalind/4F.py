import sys
from common import stripLine

def evaluateDegrees(graph):
    graph['in'] = {}
    graph['out'] = {}
    for v in graph['adj'].keys():
        adj = graph['adj'][v]
        graph['out'][v] = len(adj)
        if v not in graph['in']:
            graph['in'][v] = 0
        for a in adj:
            if a not in graph['in']:
                graph['in'][a] = 0
            if a not in graph['out']:
                graph['out'][a] = 0
                if a not in graph['adj']:
                    graph['adj'][a] = []
            graph['in'][a] += 1

def readGraph(f):
    fp = open(f, 'r')
    graph = {}
    graph['adj'] = {}
    graph['numE'] = 0
    for line in fp.readlines():
        line = stripLine(line)
        (fromV, b) = line.split(' -> ')
        toVs = b.split(',')
        graph['adj'][fromV] = toVs
        graph['numE'] += len(toVs)
    fp.close()
    evaluateDegrees(graph)
    return graph

def removeFirstEdgeOf(graph, v):
    if len(graph['adj'][v]) <= 0:
        return
    first = graph['adj'][v].pop(0)
    graph['numE'] -= 1
    return first

def moveToNextValidVertexOnCycle(cycle, graph):
    for i in range(0,len(cycle)):
        front = cycle.pop(0)
        cycle.append(front)
        if len(graph['adj'][cycle[0]]) > 0:
            break
    return cycle[0]

def findCycleFrom(graph, cycle, start):
    cycle.append(start)
    nextV = removeFirstEdgeOf(graph, start)
    while nextV is not None  and  nextV != start:
        cycle.append(nextV)
        nextV = removeFirstEdgeOf(graph, nextV)

def eulerianCycle(graph):
    cycle = []
    # any other vertex will also work
    start = graph['adj'].keys()[0]
    while graph['numE'] > 0:
        findCycleFrom(graph, cycle, start)
        start = moveToNextValidVertexOnCycle(cycle, graph)
    cycle.append(start)  # final vertex same as start in the cycle
    return cycle

def findUnbalancedNodes(graph):
    start = end = ''
    for v in graph['in'].keys():
        d = graph['in'][v] - graph['out'][v]
        if d == 1:
            end = v
        elif d == -1:
            start = v
    return (start, end)

def eulerianPath(graph):
    (start, end) = findUnbalancedNodes(graph)
    # add that edge to make it balanced
    graph['adj'][end].append(start)
    cycle = eulerianCycle(graph)
    path = []
    # break the cycle
    for i in range(1,len(cycle)):
        if cycle[i-1] == end  and  cycle[i] == start:
            path = cycle[i:] + cycle[1:i]
            break
    return path

if __name__ == '__main__':
    graph = readGraph(sys.argv[1])
    path = eulerianPath(graph)
    print '->'.join(path)
