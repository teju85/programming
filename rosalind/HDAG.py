import sys
from common import readEdgeListFromFp, topologicalSort

def hasHamiltonian(graph):
    stack = topologicalSort(graph)
    for i in range(1,len(stack)):
        (u, v) = (stack[i-1], stack[i])
        if v not in graph['adj'][u]:
            return [-1]
    out = [1]
    for s in stack:
        out.append(s+1)
    return out

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    numGraphs = int(fp.readline())
    graphs = []
    for i in range(0,numGraphs):
        g = readEdgeListFromFp(fp, directed=True)
        graphs.append(g)
    fp.close()
    for g in graphs:
        out = hasHamiltonian(g)
        for o in out:
            print o,
        print
