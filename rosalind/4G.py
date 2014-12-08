import sys
from common import stripLine

def addAnEdge(adj, a, b):
    if a not in adj:
        adj[a] = set()
    adj[a].add(b)

def addEdge(adj, dna):
    k = len(dna)
    (a, b) = (dna[0:k-1], dna[1:k])
    addAnEdge(adj, a, b)

def deBruijn(dnas):
    adj = {}
    for d in dnas:
        addEdge(adj, d)
    return adj

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

def generateGraph(dnas):
    adj = deBruijn(dnas)
    graph = {}
    graph['adj'] = {}
    graph['numE'] = 0
    for key in adj.keys():
        arr = list(adj[key])
        graph['numE'] += len(arr)
        graph['adj'][key] = arr
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

def stringSpelled(texts):
    out = texts[0]
    for i in range(1,len(texts)):
        out = out + texts[i][-1]
    return out

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    k = int(fp.readline())
    dnas = []
    for line in fp.readlines():
        dnas.append(stripLine(line))
    fp.close()
    graph = generateGraph(dnas)
    path = eulerianPath(graph)
    print stringSpelled(path)
