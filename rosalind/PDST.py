import sys
from common import readFasta, hamming

def pDistance(s, t):
    p = hamming(s, t) * 1.0 / len(s)
    return p

def distanceMatrix(dnas, distFunc):
    mat = []
    for s in dnas:
        tmp = []
        for t in dnas:
            pdst = distFunc(s[1], t[1])
            tmp.append(pdst)
        mat.append(tmp)
    return mat

def printMat(mat):
    for m in mat:
        for n in m:
            print n,
        print

if __name__ == '__main__':
    dnas = readFasta(sys.argv[1])
    m = distanceMatrix(dnas, pDistance)
    printMat(m)
