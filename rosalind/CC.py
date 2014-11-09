import sys
from common import readEdgeList, connectedComponents

if __name__ == '__main__':
    graph = readEdgeList(sys.argv[1])
    (comps, color) = connectedComponents(graph)
    print comps
    print color
