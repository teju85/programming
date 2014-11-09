import sys
import string
from common import readFasta

revMap = {}
revMap['A'] = 'T'
revMap['C'] = 'G'
revMap['G'] = 'C'
revMap['T'] = 'A'

def isRevPalin(dna):
    end = len(dna)
    mid = end / 2
    end -= 1
    for i in range(0,mid):
        if dna[i] != revMap[dna[end-i]]:
            return False
    return True

def positions(dna):
    out = []
    for length in [4, 6, 8, 10, 12]:
        for i in range(0,len(dna)-length+1):
            if isRevPalin(dna[i:i+length]):
                out.append((i+1, length))
    return out

if __name__ == '__main__':
    dna = readFasta(sys.argv[1])[0][1]
    pos = positions(dna)
    pos = sorted(pos)
    for p in pos:
        print p[0], p[1]
