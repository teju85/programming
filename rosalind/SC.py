import sys
from common import readEdgeListFromFp, topologicalSort, graphTranspose, generateAdjMatrix

def dfs(graph, node, visited, newVisited):
    visited.add(node)
    newVisited.append(node)
    for adj in graph['adj'][node]:
        if adj not in visited:
            dfs(graph, adj, visited, newVisited)

def leftToRight(left, right, graph):
    for l in left:
        adj = graph['adj'][l]
        for r in right:
            if r in adj:
                return True
    return False

def generateComponentGraph(graph, stack, origGraph):
    count = 0
    visited = set()
    nodes = []
    for node in stack:
        if node not in visited:
            newVisited = []
            count += 1
            dfs(graph, node, visited, newVisited)
            nodes.append(newVisited)
    comp = {}
    comp['numV'] = count
    comp['numE'] = 0
    comp['edges'] = []
    for i in range(0,count):
        for j in range(i+1,count):
            if leftToRight(nodes[i], nodes[j], origGraph):
                comp['edges'].append((i+1, j+1))
                comp['numE'] += 1
            elif leftToRight(nodes[j], nodes[i], origGraph):
                comp['edges'].append((j+1, i+1))
                comp['numE'] += 1
    generateAdjMatrix(comp, directed=True)
    return comp

def isInOrder(stack, comp):
    for i in range(1,len(stack)):
        adj = comp['adj'][stack[i-1]]
        if stack[i] not in adj:
            return False
    return True

def isSemiConnectedGraph(graph):
    stack = topologicalSort(graph)
    trans = graphTranspose(graph)
    comp = generateComponentGraph(trans, stack, graph)
    stack = topologicalSort(comp)
    if isInOrder(stack, comp):
        return 1
    else:
        return -1

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    k = int(fp.readline())
    graphs = []
    for i in range(0,k):
        fp.readline()
        graph = readEdgeListFromFp(fp, directed=True)
        print isSemiConnectedGraph(graph),
    print
    fp.close()
