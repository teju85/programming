import sys
from common import readEdgeList

def doubleDegree(graph):
    numV = graph['numV']
    for v in range(numV):
        sum = 0
        for n in graph['adj'][v]:
            sum = sum + graph['deg'][n]
        print sum,
    print

if __name__ == '__main__':
    graph = readEdgeList(sys.argv[1])
    doubleDegree(graph)
