import sys
from common import readFasta

def editDistance(s, t):
    ls = len(s) + 1
    lt = len(t) + 1
    mat = [ [0 for j in range(0,lt)]  for i in range(0,ls)]
    for i in range(1,ls):
        mat[i][0] = i
    for j in range(1,lt):
        mat[0][j] = j
    for i in range(1,ls):
        sa = s[i-1]
        for j in range(1,lt):
            ta = t[j-1]
            if sa == ta:
                mat[i][j] = mat[i-1][j-1]
            else:
                a = mat[i-1][j] + 1
                b = mat[i][j-1] + 1
                c = mat[i-1][j-1] + 1
                mat[i][j] = min(a, b, c)
    return mat[len(s)][len(t)]

if __name__ == '__main__':
    dnas = readFasta(sys.argv[1])
    print editDistance(dnas[0][1], dnas[1][1])
