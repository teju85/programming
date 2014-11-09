import sys
from common import stripLine, generateAdjMatrix

def _addEdge(adj, dna):
    k = len(dna)
    (a, b) = (dna[0:k-1], dna[1:k])
    found = False
    for t in adj:
        if t[0] == a  and  t[1] == b:
            found = True
            break
    if not found:
        adj.append((a, b, dna))
def deBruijn(dnas):
    adj = []
    for d in dnas:
        _addEdge(adj, d)
    adj = sorted(adj)
    return adj

def dfs(graph, node, visited, parent):
    visited.add(node)
    parent.append(node)
    for a in graph['adj'][node]:
        (adj, s) = a
        if adj in visited:
            return True
        if dfs(graph, adj, visited, parent):
            return True
    visited.remove(node)
    parent.pop(-1)
    return False

def simpleCycle(graph):
    for node in range(0,graph['numV']):
        visited = set()
        parent = []
        if dfs(graph, node, visited, parent):
            return parent
    return []

def createGraph(adjs):
    graph = {}
    graph['map'] = {}
    graph['rmap'] = {}
    numV = 0
    for a in adjs:
        if a[0] not in graph['map']:
            numV += 1
            graph['map'][a[0]] = numV
            graph['rmap'][numV] = a[0]
        if a[1] not in graph['map']:
            numV += 1
            graph['map'][a[1]] = numV
            graph['rmap'][numV] = a[1]
    graph['numV'] = numV
    graph['numE'] = 0
    graph['edges'] = []
    for a in adjs:
        u = graph['map'][a[0]]
        v = graph['map'][a[1]]
        graph['edges'].append((u, v, a[2]))
        graph['numE'] += 1
        generateAdjMatrix(graph, directed=True, weighted=True)
    return graph

def perfectCoverage(dnas):
    k = len(dnas[0]) - 2
    adjs = deBruijn(dnas)
    graph = createGraph(adjs)
    cycle = simpleCycle(graph)
    cov = graph['rmap'][cycle[0]+1]
    for i in range(1,len(cycle)-k):  # -k because last k will repeat!
        cov += graph['rmap'][cycle[i]+1][-1]
    return cov

if __name__ == '__main__':
    sys.setrecursionlimit(20000)
    fp = open(sys.argv[1], 'r')
    dnas = []
    for line in fp.readlines():
        dnas.append(stripLine(line))
    fp.close()
    print perfectCoverage(dnas)
