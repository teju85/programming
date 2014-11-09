import sys
from common import readEdgeList, topologicalSort, graphTranspose, dfs

def countSCC(graph, stack):
    count = 0
    visited = set()
    for node in stack:
        if node not in visited:
            dfs(graph, node, visited)
            count += 1
    return count

if __name__ == '__main__':
    graph = readEdgeList(sys.argv[1], directed=True)
    stack = topologicalSort(graph)
    trans = graphTranspose(graph)
    print countSCC(trans, stack)
