import sys
from common import readFasta

def backtrack(mat, s, t, i, j):
    if i <= 0 or j<= 0:
        return ('', '')
    if s[i-1] == t[j-1]:
        (s1, t1) = backtrack(mat, s, t, i-1, j-1)
        s1 += s[i-1]
        t1 += t[j-1]
    elif mat[i][j-1] <= mat[i-1][j]  and  mat[i][j-1] <= mat[i-1][j-1]:
        (s1, t1) = backtrack(mat, s, t, i, j-1)
        s1 += '-'
        t1 += t[j-1]
    elif mat[i-1][j] <= mat[i-1][j-1]:
        (s1, t1) = backtrack(mat, s, t, i-1, j)
        s1 += s[i-1]
        t1 += '-'
    else:
        (s1, t1) = backtrack(mat, s, t, i-1, j-1)
        s1 += s[i-1]
        t1 += t[j-1]
    return (s1, t1)

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
    (s1, t1) = backtrack(mat, s, t, ls-1, lt-1)
    (score, s1, t1) = (mat[len(s)][len(t)], s1, t1)
    return (score, s1, t1)

if __name__ == '__main__':
    dnas = readFasta(sys.argv[1])
    (score, s1, t1) = editDistance(dnas[0][1], dnas[1][1])
    print score
    print s1
    print t1
