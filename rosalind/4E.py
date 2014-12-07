import sys
from common import stripLine

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

if __name__ == '__main__':
    graph = readGraph(sys.argv[1])
    cycle = eulerianCycle(graph)
    print '->'.join(cycle)
