import sys


def chromosome2cycle(chrom):
    out = []
    for j in range(0,len(chrom)):
        i = chrom[j]
        if i > 0:
            out.append(2*i - 1)
            out.append(2*i)
        else:
            out.append(-(2*i))
            out.append(-(2*i) - 1)
    return out

def getEdges(chroms):
    edges = []
    for chrom in chroms:
        nodes = chromosome2cycle(chrom)
        nodes.append(nodes[0])
        for j in range(0,len(chrom)):
            edges.append((nodes[2*j+1], nodes[2*j+2]))
            edges.append((nodes[2*j], nodes[2*j+1]))
    return edges

def coloredEdges(chroms):
    edges = []
    for chrom in chroms:
        nodes = chromosome2cycle(chrom)
        nodes.append(nodes[0])
        for j in range(0,len(chrom)):
            edges.append((nodes[2*j+1], nodes[2*j+2]))
    return edges

def generateGraph(edges):
    graph = {}
    graph['edges'] = edges
    graph['numE'] = len(edges) * 2  # undirected
    graph['adj'] = {}
    graph['verts'] = set()
    for e in graph['edges']:
        x = e[0]
        y = e[1]
        graph['verts'].add(x)
        graph['verts'].add(y)
        if x not in graph['adj']:
            graph['adj'][x] = []
        if y not in graph['adj']:
            graph['adj'][y] = []
        graph['adj'][x].append(y)
        graph['adj'][y].append(x)
    graph['numV'] = len(graph['verts'])
    return graph

def countCycles(edgesP, edgesQ):
    graphP = generateGraph(edgesP)
    graphQ = generateGraph(edgesQ)
    cycles = 0
    visited = set()
    for node in graphP['verts']:
        if node in visited:
            continue
        stack = [(node, True)]
        while len(stack) > 0:
            (top, pickP) = stack.pop(-1)
            if top in visited:
                cycles += 1
                break
            visited.add(top)
            if pickP:
                graph = graphP
                pickP = False
            else:
                graph = graphQ
                pickP = True
            for adj in graph['adj'][top]:
                stack.append((adj, pickP))
    return cycles

def distance(edgesP, edgesQ):
    return (len(edgesP) - countCycles(edgesP, edgesQ))

def getChromosomes(line):
    line = line.strip('\n')
    line = line.strip('\r')
    line = line.strip('(')
    line = line.strip(')')
    chroms = []
    for ll in line.split(')('):
        chrom = map(int, ll.split(' '))
        chroms.append(chrom)
    return chroms


if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    P = getChromosomes(fp.readline())
    Q = getChromosomes(fp.readline())
    fp.close()
    edgesP = coloredEdges(P)
    edgesQ = coloredEdges(Q)
    print distance(edgesP, edgesQ)
