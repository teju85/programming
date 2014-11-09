import sys
from common import stripLine
from newick import newick

def distance(graph, source, dest):
    dist = [0   for i in range(0,graph['numV'])]
    frontier = []
    frontier.append(source)
    visited = set()
    visited.add(source)
    while len(frontier) > 0:
        node = frontier[0]
        del frontier[0]
        found = False
        for adj in graph['adj'][node]:
            if adj not in visited:
                frontier.append(adj)
                visited.add(adj)
                dist[adj] = dist[node] + 1
            if adj == dest:
                found = True
                break
    return dist[dest]

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    idx = 0
    nwck = ''
    data = []
    for line in fp.readlines():
        line = stripLine(line)
        if len(line) <= 0:
            continue
        if idx == 1:
            idx = 0
            (src, dst) = line.split(' ')
            data.append((nwck, src, dst))
        else:
            idx += 1
            nwck = line
    fp.close()
    for d in data:
        tree = newick(d[0])
        #print tree
        print distance(tree, tree['map'][d[1]]-1, tree['map'][d[2]]-1),
    print
