import sys
from common import stripLine

def addAnEdge(adj, a, b):
    if a not in adj:
        adj[a] = set()
    adj[a].add(b)

def addEdge(adj, dna):
    k = len(dna)
    (a, b) = (dna[0:k-1], dna[1:k])
    addAnEdge(adj, a, b)

def deBruijn(dnas):
    adj = {}
    for d in dnas:
        addEdge(adj, d)
    return adj

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    dnas = []
    for line in fp.readlines():
        dnas.append(stripLine(line))
    fp.close()
    adj = deBruijn(dnas)
    for a in sorted(adj.keys()):
        print "%s -> %s" % (a, ','.join(sorted(adj[a])))
