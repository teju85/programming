import sys
import string
from common import readFasta

def getProfileMatrix(data):
    mat = {}
    size = len(data[0][1])
    for c in 'ACGT':
        mat[c] = [0] * size
    for i in range(0,size):
        for d in data:
            dna = d[1]
            mat[dna[i]][i] += 1
    return mat

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

if __name__ == '__main__':
    data = readFasta(sys.argv[1])
    profMat = getProfileMatrix(data)
    consStr = consensusString(profMat)
    print consStr
    for c in 'ACGT':
        print '%s:' % (c),
        for v in profMat[c]:
            print v,
        print
