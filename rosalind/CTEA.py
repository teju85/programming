import sys
from common import readFasta

prime = 134217727

def editDistance(s, t):
    ls = len(s) + 1
    lt = len(t) + 1
    mat = [ [0 for j in range(0,lt)]  for i in range(0,ls)]
    count = [ [0 for j in range(0,lt)]  for i in range(0,ls)]
    for i in range(1,ls):
        mat[i][0] = i
        count[i][0] = 1
    for j in range(1,lt):
        mat[0][j] = j
        count[0][j] = 1
    count[0][0] = 1
    for i in range(1,ls):
        sa = s[i-1]
        for j in range(1,lt):
            ta = t[j-1]
            if sa == ta:
                mat[i][j] = mat[i-1][j-1]
                a = mat[i-1][j] + 1
                b = mat[i][j-1] + 1
                c = mat[i-1][j-1]
                m = min(a, b, c)
                if m == a:
                    count[i][j] += count[i-1][j]
                if m == b:
                    count[i][j] += count[i][j-1]
                if m == c:
                    count[i][j] += count[i-1][j-1]
            else:
                a = mat[i-1][j] + 1
                b = mat[i][j-1] + 1
                c = mat[i-1][j-1] + 1
                m = min(a, b, c)
                mat[i][j] = m
                if m == a:
                    count[i][j] += count[i-1][j]
                if m == b:
                    count[i][j] += count[i][j-1]
                if m == c:
                    count[i][j] += count[i-1][j-1]
                count[i][j] %= prime
    score = count[-1][-1]
    return score

if __name__ == '__main__':
    dnas = readFasta(sys.argv[1])
    score = editDistance(dnas[0][1], dnas[1][1])
    print score
