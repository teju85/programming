import sys
from common import readAdjList, connectedComponents

if __name__ == '__main__':
    graph = readAdjList(sys.argv[1])
    (comps, color) = connectedComponents(graph)
    print comps
    print color-1
