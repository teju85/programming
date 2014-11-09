import sys
from common import readEdgeList, topologicalSort

if __name__ == '__main__':
    graph = readEdgeList(sys.argv[1], directed=True)
    stack = topologicalSort(graph)
    for s in stack:
        print s+1,
    print
