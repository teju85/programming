import sys
import random
from common import readIntTriplet, stripLine, hamming

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

def getKmerProbs(dna, k, profile):
    probs = []
    total = 0.0
    for i in range(0,len(dna)-k+1):
        kmer = dna[i:i+k]
        p = probOfKmer(kmer, profile)
        total += p
        probs.append(p)
    for i in range(0,len(probs)):
        probs[i] /= total
    return probs

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

def getProfileRandomMotif(prob, dna, k):
    probs = getKmerProbs(dna, k, prob)
    r = random.uniform(0.0, 1.0)
    soFar = 0.0
    for pos in range(0,len(probs)):
        soFar += probs[pos]
        if r < soFar:
            return dna[pos:pos+k]
    return dna[len(probs)-1:len(probs)-1+k]

def gibbsSampler(dnas, k, t, N):
    bestMotifs = generateRandomMotifs(dnas, k)
    bestScore = score(bestMotifs)
    size = len(dnas[0])
    while N > 0:
        i = random.randint(0,t-1)
        noImotifs = bestMotifs[0:i] + bestMotifs[i+1:]
        (mat, prob) = getProfileMatrix(noImotifs, pseudocounts=True)
        motif = getProfileRandomMotif(prob, dnas[i], k)
        motifs = bestMotifs[0:i] + [motif] + bestMotifs[i+1:]
        currScore = score(motifs)
        if currScore < bestScore:
            bestScore = currScore
            bestMotifs = motifs
        N -= 1
    return (bestMotifs, bestScore)

def multipleTimes(dnas, k, t, N, numIter):
    bestM = []
    bestScore = 1000000000
    while numIter > 0:
        (m, s) = gibbsSampler(dnas, k, t, N)
        if s < bestScore:
            bestScore = s
            bestM = m
        numIter -= 1
    return (bestM, bestScore)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    (k, t, N) = readIntTriplet(fp)
    dnas = []
    for line in fp.readlines():
        dnas.append(stripLine(line))
    fp.close()
    (motifs, sc) = multipleTimes(dnas, k, t, N, 20)
    for m in motifs:
        print m
    print sc
