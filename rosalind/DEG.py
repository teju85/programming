import sys
from common import readEdgeList

def degree(graph):
    numV = graph['numV']
    deg = {}
    for i in range(numV):
        deg[i+1] = 0
    for e in graph['edges']:
        deg[e[0]] = deg[e[0]] + 1
        deg[e[1]] = deg[e[1]] + 1
    for k in deg.keys():
        print deg[k],
    print

if __name__ == '__main__':
    graph = readEdgeList(sys.argv[1])
    degree(graph)
