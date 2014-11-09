import sys
from common import readFasta

def isTransition(a, b):
    if a == 'A' and b == 'G':
        return True
    if a == 'G' and b == 'A':
        return True
    if a == 'C' and b == 'T':
        return True
    if a == 'T' and b == 'C':
        return True

def ratio(s1, s2):
    transi = 0
    transv = 0
    for i in range(0, len(s1)):
        if s1[i] == s2[i]:
            continue
        if isTransition(s1[i], s2[i]):
            transi += 1
        else:
            transv += 1
    ratio = transi * 1.0 / transv
    return ratio

if __name__ == '__main__':
    dnas = readFasta(sys.argv[1])
    print ratio(dnas[0][1], dnas[1][1])
