import sys
from common import readEdgeListFromFp

def bfs(graph, source, colors):
    frontier = []
    frontier.append(source)
    visited = set()
    visited.add(source)
    colors[source] = 0
    while len(frontier) > 0:
        node = frontier[0]
        del frontier[0]
        for adj in graph['adj'][node]:
            neighColor = (colors[node] + 1) % 2
            if adj not in visited:
                frontier.append(adj)
                visited.add(adj)
                colors[adj] = neighColor
            elif colors[adj] != neighColor:
                return False
    return True

def isBip(graph):
    colors = {}
    for v in range(0, graph['numV']):
        if v in colors:
            continue
        if not bfs(graph, v, colors):
            return False
    return True

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    numGraphs = int(fp.readline())
    graphs = []
    for i in range(0,numGraphs):
        fp.readline()
        g = readEdgeListFromFp(fp)
        graphs.append(g)
    fp.close()
    for g in graphs:
        if isBip(g):
            print 1,
        else:
            print -1,
    print
