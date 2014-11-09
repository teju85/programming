import sys
from common import stripLine

def _canInterweave(dna, s, t):
    k = len(s) + len(t)
    if len(dna) < k:
        return False
    if len(s) <= 0  and  len(t) > 0:
        if dna[0:len(t)] == t:
            return True
        return False
    if len(t) <= 0  and  len(s) > 0:
        if dna[0:len(s)] == s:
            return True
        return False
    if dna[0] == s[0]  and  _canInterweave(dna[1:], s[1:], t):
        return True
    if dna[0] == t[0]  and  _canInterweave(dna[1:], s, t[1:]):
        return True
    return False

def areDisjointMotifs(dna, s, t):
    k = len(s) + len(t)
    for i in range(0,len(dna)-k+1):
        if dna[i] == s[0]  and  _canInterweave(dna[i:], s, t):
            return True
        if dna[i] == t[0]  and  _canInterweave(dna[i:], s, t):
            return True
    return False

def disjoints(dna, motifs):
    lm = len(motifs)
    mat = [[0 for i in range(0,lm)] for j in range(0,lm)]
    for i in range(0,lm):
        for j in range(i,lm):
            if areDisjointMotifs(dna, motifs[i], motifs[j]):
                mat[i][j] = mat[j][i] = 1
    return mat

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    motifs = []
    dna = stripLine(fp.readline())
    for line in fp.readlines():
        motifs.append(stripLine(line))
    fp.close()
    mat = disjoints(dna, motifs)
    for m in mat:
        for n in m:
            print n,
        print
