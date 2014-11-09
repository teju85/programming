import sys
from common import readFasta

def getFailureArray(dna):
    P = [-1]
    j = -1
    for i in range(1,len(dna)):
        first = True
        while j >= 0  and  dna[j] != dna[i]:
            if first:
                j = P[j-1] + 1
            else:
                j = P[j]
            first = False
        if j == -1  and  dna[0] == dna[i]:
            j = 0
        P.append(j)
        j += 1
    for i in range(0,len(P)):
        P[i] += 1
    return P

if __name__ == '__main__':
    dna = readFasta(sys.argv[1])[0][1]
    P = getFailureArray(dna)
    for p in P:
        print p,
    print
