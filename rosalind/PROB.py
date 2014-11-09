import sys
from common import readFloatArrayFromLine, stripLine
import math

def ACGThist(dna):
    hist = {'A':0, 'C':0, 'G':0, 'T':0}
    for s in dna:
        hist[s] += 1
    return hist

def getLogProb(gcProb):
    logProb = {}
    acProb = math.log10((1 - gcProb) / 2)
    gcProb = math.log10(gcProb / 2)
    logProb['A'] = acProb
    logProb['T'] = acProb
    logProb['C'] = gcProb
    logProb['G'] = gcProb
    return logProb

def randomMatch(gcProb, dnaHist):
    logProb = getLogProb(gcProb)
    prob = 0.0
    for s in 'ACGT':
        prob += (dnaHist[s] * logProb[s])
    return prob

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    s = stripLine(fp.readline())
    A = readFloatArrayFromLine(fp)
    fp.close()
    dnaHist = ACGThist(s)
    for a in A:
        print randomMatch(a, dnaHist),
    print
