import sys
from common import readFasta

def subsequenceBacktrack(mat, s, t, i, j):
    if i <= 0 or j<= 0:
        return ''
    if s[i-1] == t[j-1]:
        out = subsequenceBacktrack(mat, s, t, i-1, j-1) + s[i-1]
    elif mat[i][j-1] >= mat[i-1][j]:
        out = subsequenceBacktrack(mat, s, t, i, j-1)
    else:
        out = subsequenceBacktrack(mat, s, t, i-1, j)
    return out

def longestCommonSubsequence(s, t):
    ls = len(s) + 1
    lt = len(t) + 1
    mat = [ [0 for j in range(0,lt)]  for i in range(0,ls)]
    for i in range(1,ls):
        sa = s[i-1]
        for j in range(1,lt):
            ta = t[j-1]
            if sa == ta:
                mat[i][j] = mat[i-1][j-1] + 1
            else:
                a = mat[i-1][j]
                b = mat[i][j-1]
                mat[i][j] = max(a, b)
    return subsequenceBacktrack(mat, s, t, ls-1, lt-1)

if __name__ == '__main__':
    dnas = readFasta(sys.argv[1])
    sys.setrecursionlimit(10000)
    print longestCommonSubsequence(dnas[0][1], dnas[1][1])
