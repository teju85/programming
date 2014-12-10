import sys
from common import stripLine

def addAnEdge(adj, a, b):
    if a not in adj:
        adj[a] = []
    adj[a].append(b)

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
    graph['adj'] = adj
    graph['numE'] = 0
    for key in adj.keys():
        graph['numE'] += len(adj[key])
    evaluateDegrees(graph)
    graph['vertices'] = sorted(graph['in'].keys())
    return graph

def oneInOneOut(v, graph):
    if graph['in'][v] == graph['out'][v]:
        if graph['in'][v] == 1:
            return True
    return False

def branchStartAt(v, graph):
    if not oneInOneOut(v, graph)  and  graph['out'][v] > 0:
        return True
    return False

def maximalNonBranchingPaths(graph):
    maxPaths = []
    for v in graph['vertices']:
        if branchStartAt(v, graph):
            for adj in graph['adj'][v]:
                #graph['out'][v] -= 1
                w = adj
                path = [v, w]
                while oneInOneOut(w, graph):
                    graph['in'][w] -= 1
                    graph['out'][w] -= 1
                    w = graph['adj'][w][0]
                    path.append(w)
                #graph['in'][w] -= 1  # last vertex in the path
                maxPaths.append(path)
    for v in graph['vertices']:
        if oneInOneOut(v, graph):
            #graph['out'][v] -= 1
            w = graph['adj'][v][0]
            path = [v, w]
            while oneInOneOut(w, graph):
                graph['in'][w] -= 1
                graph['out'][w] -= 1
                w = graph['adj'][w][0]
                path.append(w)
                if w == v:
                    break
            #graph['in'][w] -= 1  # last vertex in the path
            maxPaths.append(path)
    return maxPaths

def stringSpelled(texts):
    out = texts[0]
    for i in range(1,len(texts)):
        out = out + texts[i][-1]
    return out

def allPaths(paths):
    out = []
    for p in paths:
        out.append(stringSpelled(p))
    out = sorted(out)
    for o in out:
        print o

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    dnas = []
    for line in fp.readlines():
        dnas.append(stripLine(line))
    fp.close()
    graph = generateGraph(dnas)
    paths = maximalNonBranchingPaths(graph)
    allPaths(paths)
