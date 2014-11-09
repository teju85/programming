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

def getAllKmers(dna, k):
    dnas = []
    for i in range(0,len(dna)-k+1):
        dnas.append(dna[i:i+k])
    return dnas

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    k = int(fp.readline())
    dna = stripLine(fp.readline())
    fp.close()
    dnas = getAllKmers(dna, k)
    adj = deBruijn(dnas)
    for a in sorted(adj.keys()):
        print "%s -> %s" % (a, ','.join(adj[a]))
