import sys
from common import readIntPair, stripLine, hamming

def getProfileMatrix(data):
    mat = {}
    prob = {}
    size = len(data[0])
    for c in 'ACGT':
        mat[c] = [0] * size
        prob[c] = [0.0] * size
    for i in range(0,size):
        for dna in data:
            mat[dna[i]][i] += 1
    for i in range(0,size):
        s = 0
        for c in 'ACGT':
            s += mat[c][i]
        for c in 'ACGT':
            prob[c][i] = mat[c][i] * 1.0 / s
    return (mat, prob)

def maxChar(mat, i):
    maxC = ''
    maxV = -1
    for c in 'ACGT':
        if maxV < mat[c][i]:
            maxV = mat[c][i]
            maxC = c
    return maxC

def consensusString(mat):
    size = len(mat['A'])
    conStr = ''
    for i in range(0,size):
        conStr += maxChar(mat, i)
    return conStr

def probOfKmer(kmer, profile):
    prob = 1.0
    for i in range(0,len(kmer)):
        prob *= profile[kmer[i]][i]
    return prob

def mostProbableKmer(dna, k, profile):
    maxProb = -1.0
    maxKmer = ''
    for i in range(0,len(dna)-k+1):
        kmer = dna[i:i+k]
        p = probOfKmer(kmer, profile)
        if p > maxProb:
            maxProb = p
            maxKmer = kmer
    return maxKmer

def score(motifs):
    (mat, prob) = getProfileMatrix(motifs)
    cs = consensusString(mat)
    outScore = 0
    for m in motifs:
        outScore += hamming(m, cs)
    return outScore

def greedyMotifSearch(dnas, k, t):
    bestMotifs = []
    bestScore = len(dnas) * len(dnas[0])
    size = len(dnas[0])
    for i in range(0,size-k+1):
        motifs = [dnas[0][i:i+k]]
        for j in range(1,t):
            (mat, prob) = getProfileMatrix(motifs)
            mostProbable = mostProbableKmer(dnas[j], k, prob)
            motifs.append(mostProbable)
        currScore = score(motifs)
        if currScore < bestScore:
            bestScore = currScore
            bestMotifs = motifs
    return bestMotifs

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    (k, t) = readIntPair(fp)
    dnas = []
    for line in fp.readlines():
        dnas.append(stripLine(line))
    fp.close()
    motifs = greedyMotifSearch(dnas, k, t)
    for m in motifs:
        print m
