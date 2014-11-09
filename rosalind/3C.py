import sys
from common import readFloatArrayFromLine, stripLine

dnaMap = {'A':0, 'C':1, 'G':2, 'T':3}

def probOfKmer(kmer, profile):
    prob = 1.0
    for i in range(0,len(kmer)):
        row = dnaMap[kmer[i]]
        prob *= profile[row][i]
    return prob

def mostProbableKmer(dna, k, profile):
    maxProb = 0.0
    maxKmer = ''
    for i in range(0,len(dna)-k+1):
        kmer = dna[i:i+k]
        p = probOfKmer(kmer, profile)
        if p > maxProb:
            maxProb = p
            maxKmer = kmer
    return maxKmer

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    dna = stripLine(fp.readline())
    k = int(fp.readline())
    profile = []
    for i in range(0,4):
        profile.append(readFloatArrayFromLine(fp))
    fp.close()
    print mostProbableKmer(dna, k, profile)
