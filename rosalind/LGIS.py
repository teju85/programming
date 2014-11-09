import sys
from common import readArrayFromLine

def lcsm(a, b):
    la = len(a) + 1
    lb = len(b) + 1
    mat = [[0 for x in range(0,lb)] for x in range(0,la)]
    maxLen = 0
    for i in range(1,la):
        ca = a[i-1]
        for j in range(1,lb):
            cb = b[j-1]
            if ca == cb:
                mat[i][j] = mat[i-1][j-1] + 1
            else:
                mat[i][j] = max(mat[i-1][j], mat[i][j-1])
    return mat

def backtrack(mat, a, b, i, j):
    out = []
    while i > 0  and  j > 0:
        if a[i-1] == b[j-1]:
            out = [a[i-1]] + out
            i -= 1
            j -= 1
        elif mat[i][j-1] > mat[i-1][j]:
            j -= 1
        else:
            i -= 1
    for o in out:
        print o,
    print

def lis(pi, n):
    a = pi
    b = range(1,n+1)
    mat = lcsm(a, b)
    backtrack(mat, a, b, len(a), len(b))

def lds(pi, n):
    a = pi
    b = range(n,0,-1)
    mat = lcsm(a, b)
    backtrack(mat, a, b, len(a), len(b))

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    n = int(fp.readline())
    pi = readArrayFromLine(fp)
    fp.close()
    lis(pi, n)
    lds(pi, n)
