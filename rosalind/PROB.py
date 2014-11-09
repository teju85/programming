import sys
from common import readFloatArrayFromLine, stripLine, ACGThist, getLogProb
import math

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
