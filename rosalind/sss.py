from common import generateAdjMatrix

def suffixOverlap(x, y):
    for i in range(len(x),0,-1):
        if i > len(y):
            continue
        if x[-i:] == y[0:i]:
            return i
    return 0

def generateGraph(dnas, fmt='fasta'):
    isFasta = (fmt == 'fasta')
    graph = {}
    graph['numV'] = len(dnas)
    graph['numE'] = 0
    graph['edges'] = []
    for i in range(0,len(dnas)):
        for j in range(0,len(dnas)):
            if i == j:
                continue
            if isFasta:
                over = suffixOverlap(dnas[i][1], dnas[j][1])
            else:
                over = suffixOverlap(dnas[i], dnas[j])
            if over <= 0:
                continue
            # -over because we are finding MST!
            graph['edges'].append((i+1,j+1,-over))
            graph['numE'] += 1
    generateAdjMatrix(graph, directed=True, weighted=True)
    return graph

def dfs(graph, node, visited):
    visited[node] = 1
    for a in graph['adj'][node]:
        (adj, weight) = a
        if adj in visited:
            return False
        if not dfs(graph, adj, visited):
            return False
    del visited[node]
    return True

def isDAG(graph):
    finishedNodes = {}
    for node in range(0,graph['numV']):
        visited = {}
        if not dfs(graph, node, visited):
            return False
    return True

def createEmptyGraph(inGraph):
    out = {}
    out['edges'] = []
    out['numV'] = inGraph['numV']
    out['numE'] = 0
    generateAdjMatrix(out, directed=True, weighted=True)
    return out

def getAllEdges(graph):
    edges = []
    for e in graph['edges']:
        edges.append((e[2], e[0], e[1]))
    edges = sorted(edges)
    return edges

def addAnEdgeTo(graph, edge):
    graph['edges'].append(edge)
    graph['numE'] += 1
    generateAdjMatrix(graph, directed=True, weighted=True)

def removeLastEdgeFrom(graph):
    graph['edges'].pop()
    graph['numE'] -= 1
    generateAdjMatrix(graph, directed=True, weighted=True)

def removeReverseEdgeInList(edges, first):
    #if first in edges:
    #    edges.remove(first)
    for i in range(0,len(edges)):
        if edges[i][0] == first[0]  and  edges[i][1] == first[1]  and  edges[i][2] == first[2]:
            edges.pop(i)
            return

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

def constructSuperString(stack, dnas, graph, fmt='fasta'):
    isFasta = (fmt == 'fasta')
    superStr = ''
    for s in stack:
        if isFasta:
            tmp = dnas[s][1]
        else:
            tmp = dnas[s]
        over = suffixOverlap(superStr, tmp)
        if over <= 0:
            superStr += tmp
        else:
            superStr += tmp[over:]
    return superStr

def shortestSuperString(dnas, fmt='fasta'):
    graph = generateGraph(dnas, fmt)
    edges = getAllEdges(graph)
    mst = createEmptyGraph(graph)
    while (mst['numE'] < mst['numV']-1)  and  (len(edges) > 0):
        first = edges.pop(0)
        addAnEdgeTo(mst, (first[1], first[2], first[0]))
        if not isDAG(mst):
            removeLastEdgeFrom(mst)
        else:
            removeReverseEdgeInList(edges, first)
    stack = topologicalSort(mst)
    superStr = constructSuperString(stack, dnas, graph, fmt)
    return superStr
