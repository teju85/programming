import sys
from common import stripLine

def supersequenceBacktrack(mat, s, t, i, j):
    if i <= 0  and  j > 0:
        return t[0:j]
    elif i > 0  and  j <= 0:
        return s[0:i]
    elif i <= 0  and  j <= 0:
        return ''
    if s[i-1] == t[j-1]:
        out = supersequenceBacktrack(mat, s, t, i-1, j-1) + s[i-1]
    elif mat[i][j-1] <= mat[i-1][j]:
        out = supersequenceBacktrack(mat, s, t, i, j-1) + t[j-1]
    else:
        out = supersequenceBacktrack(mat, s, t, i-1, j) + s[i-1]
    return out

def shortestSuperSequence(s, t):
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
                mat[i][j] = mat[i-1][j-1] + 1
            else:
                a = mat[i-1][j] + 1
                b = mat[i][j-1] + 1
                mat[i][j] = min(a, b)
    return supersequenceBacktrack(mat, s, t, ls-1, lt-1)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    s = stripLine(fp.readline())
    t = stripLine(fp.readline())
    fp.close()
    sys.setrecursionlimit(10000)
    print shortestSuperSequence(s, t)
