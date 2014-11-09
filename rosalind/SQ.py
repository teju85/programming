import sys
from common import readEdgeListFromFp

def generateNeighborSet(graph):
    graph['neigh'] = []
    for i in range(graph['numV']):
        graph['neigh'].append(set())
    for e in graph['edges']:
        x = e[0] - 1
        y = e[1] - 1
        graph['neigh'][x].add(y)
        graph['neigh'][y].add(x)

def isUAG4(graph):
    for i in range(0,graph['numV']):
        for j in range(i+1,graph['numV']):
            inter = graph['neigh'][i].intersection(graph['neigh'][j])
            if len(inter) > 1:
                return True
    return False

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    numGraphs = int(fp.readline())
    graphs = []
    for i in range(0,numGraphs):
        fp.readline()
        g = readEdgeListFromFp(fp, directed=False)
        generateNeighborSet(g)
        graphs.append(g)
    fp.close()
    for g in graphs:
        if isUAG4(g):
            print 1,
        else:
            print -1,
    print
