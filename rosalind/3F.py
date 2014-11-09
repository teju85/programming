import sys
import random
from common import readIntPair, stripLine, hamming

def getProfileMatrix(data, pseudocounts=False):
    mat = {}
    prob = {}
    size = len(data[0])
    for c in 'ACGT':
        mat[c] = [0] * size
        prob[c] = [0.0] * size
    for i in range(0,size):
        for dna in data:
            mat[dna[i]][i] += 1
    if pseudocounts:
        for i in range(0,size):
            for c in 'ACGT':
                mat[c][i] += 1
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

def generateRandomMotifs(dnas, k):
    size = len(dnas[0])
    motifs = []
    for dna in dnas:
        pos = random.randint(0,size-k)
        motifs.append(dna[pos:pos+k])
    return motifs

def getMotifs(prob, dnas, k):
    motifs = []
    size = len(dnas[0])
    for dna in dnas:
        tmp = mostProbableKmer(dna, k, prob)
        motifs.append(tmp)
    return motifs

def randomizedMotifSearch(dnas, k, t):
    bestMotifs = generateRandomMotifs(dnas, k)
    bestScore = score(bestMotifs)
    size = len(dnas[0])
    while True:
        (mat, prob) = getProfileMatrix(bestMotifs, pseudocounts=True)
        motifs = getMotifs(prob, dnas, k)
        currScore = score(motifs)
        if currScore < bestScore:
            bestScore = currScore
            bestMotifs = motifs
        else:
            return (bestMotifs, bestScore)
    return (bestMotifs, bestScore)

def multipleTimes(dnas, k, t, numIter):
    bestM = []
    bestScore = 1000000000
    while numIter > 0:
        (m, s) = randomizedMotifSearch(dnas, k, t)
        if s < bestScore:
            bestScore = s
            bestM = m
        numIter -= 1
    return bestM

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    (k, t) = readIntPair(fp)
    dnas = []
    for line in fp.readlines():
        dnas.append(stripLine(line))
    fp.close()
    motifs = multipleTimes(dnas, k, t, 1000)
    for m in motifs:
        print m
