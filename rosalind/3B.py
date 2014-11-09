import sys
from common import stripLine, patt2num, num2patt, hamming

n2pMap = {}
n2pMap[0] = 'A'
n2pMap[1] = 'C'
n2pMap[2] = 'G'
n2pMap[3] = 'T'

def minHammingDistance(dna, patt):
    k = len(patt)
    minH = k
    for i in range(0,len(dna)-k+1):
        h = hamming(dna[i:i+k], patt)
        if h < minH:
            minH = h
    return minH

def minDistance(dnas, patt):
    out = 0
    for d in dnas:
        out += minHammingDistance(d, patt)
    return out

def medianString(dnas, k):
    limit = 4**k
    minDist = limit
    minPatt = ''
    for i in range(0,limit):
        patt = num2patt(i, k, n2pMap)
        dist = minDistance(dnas, patt)
        if dist < minDist:
            minDist = dist
            minPatt = patt
    return (minDist, minPatt)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    k = int(fp.readline())
    dnas = []
    for line in fp.readlines():
        dnas.append(stripLine(line))
    fp.close()
    print medianString(dnas, k)
