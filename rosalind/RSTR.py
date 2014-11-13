import sys
from common import stripLine, ACGThist, getLogProb
import math

def getProb(N, gc, dna):
    hist = ACGThist(dna)
    logProb = getLogProb(gc)
    prob = 0.0
    for s in 'ACGT':
        prob += (hist[s] * logProb[s])
    prob = 10 ** prob
    print prob

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    line = fp.readline()
    arr = line.split(' ')
    N = int(arr[0])
    gc = float(arr[1])
    dna = stripLine(fp.readline())
    fp.close()
    print getProb(N, gc, dna)
