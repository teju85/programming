import sys
from common import stripLine

syms = {
    'A' : 0,
    'C' : 1,
    'D' : 2,
    'E' : 3,
    'F' : 4,
    'G' : 5,
    'H' : 6,
    'I' : 7,
    'K' : 8,
    'L' : 9,
    'M' : 10,
    'N' : 11,
    'P' : 12,
    'Q' : 13,
    'R' : 14,
    'S' : 15,
    'T' : 16,
    'V' : 17,
    'W' : 18,
    'Y' : 19,
}

score = [
    [ 4,  0, -2, -1, -2,  0, -2, -1, -1, -1, -1, -2, -1, -1, -1,  1,  0,  0, -3, -2],
    [ 0,  9, -3, -4, -2, -3, -3, -1, -3, -1, -1, -3, -3, -3, -3, -1, -1, -1, -2, -2],
    [-2, -3,  6,  2, -3, -1, -1, -3, -1, -4, -3,  1, -1,  0, -2,  0, -1, -3, -4, -3],
    [-1, -4,  2,  5, -3, -2,  0, -3,  1, -3, -2,  0, -1,  2,  0,  0, -1, -2, -3, -2],
    [-2, -2, -3, -3,  6, -3, -1,  0, -3,  0,  0, -3, -4, -3, -3, -2, -2, -1,  1,  3],
    [ 0, -3, -1, -2, -3,  6, -2, -4, -2, -4, -3,  0, -2, -2, -2,  0, -2, -3, -2, -3],
    [-2, -3, -1,  0, -1, -2,  8, -3, -1, -3, -2,  1, -2,  0,  0, -1, -2, -3, -2,  2],
    [-1, -1, -3, -3,  0, -4, -3,  4, -3,  2,  1, -3, -3, -3, -3, -2, -1,  3, -3, -1],
    [-1, -3, -1,  1, -3, -2, -1, -3,  5, -2, -1,  0, -1,  1,  2,  0, -1, -2, -3, -2],
    [-1, -1, -4, -3,  0, -4, -3,  2, -2,  4,  2, -3, -3, -2, -2, -2, -1,  1, -2, -1],
    [-1, -1, -3, -2,  0, -3, -2,  1, -1,  2,  5, -2, -2,  0, -1, -1, -1,  1, -1, -1],
    [-2, -3,  1,  0, -3,  0,  1, -3,  0, -3, -2,  6, -2,  0,  0,  1,  0, -3, -4, -2],
    [-1, -3, -1, -1, -4, -2, -2, -3, -1, -3, -2, -2,  7, -1, -2, -1, -1, -2, -4, -3],
    [-1, -3,  0,  2, -3, -2,  0, -3,  1, -2,  0,  0, -1,  5,  1,  0, -1, -2, -2, -1],
    [-1, -3, -2,  0, -3, -2,  0, -3,  2, -2, -1,  0, -2,  1,  5, -1, -1, -3, -3, -2],
    [ 1, -1,  0,  0, -2,  0, -1, -2,  0, -2, -1,  1, -1,  0, -1,  4,  1, -2, -3, -2],
    [ 0, -1, -1, -1, -2, -2, -2, -1, -1, -1, -1,  0, -1, -1, -1,  1,  5,  0, -2, -2],
    [ 0, -1, -3, -2, -1, -3, -3,  3, -2,  1,  1, -3, -2, -2, -3, -2,  0,  4, -3, -1],
    [-3, -2, -4, -3,  1, -2, -2, -3, -3, -2, -1, -4, -4, -2, -3, -3, -2, -3, 11,  2],
    [-2, -2, -3, -2,  3, -3,  2, -1, -2, -1, -1, -2, -3, -1, -2, -2, -2, -1,  2,  7]
]

gapPenalty = -5

def backtrack(back, s, t, i, j):
    if i <= 0:
        if j <= 0:
            return ('', '')
        else:
            return ('-'*j, t[0:j])
    if j <= 0:
        if i <= 0:
            return ('', '')
        else:
            return (s[0:i], '-'*i)
    direction = back[i][j]
    if direction == 0:
        (s1, t1) = backtrack(back, s, t, i-1, j)
        s1 += s[i-1]
        t1 += '-'
    elif direction == 1:
        (s1, t1) = backtrack(back, s, t, i, j-1)
        s1 += '-'
        t1 += t[j-1]
    else:
        (s1, t1) = backtrack(back, s, t, i-1, j-1)
        s1 += s[i-1]
        t1 += t[j-1]
    return (s1, t1)

def editDistance(s, t):
    ls = len(s) + 1
    lt = len(t) + 1
    mat = [ [0 for j in range(0,lt)]  for i in range(0,ls)]
    back = [ [-1 for j in range(0,lt)]  for i in range(0,ls)]
    for i in range(1,ls):
        mat[i][0] = i * gapPenalty
    for j in range(1,lt):
        mat[0][j] = j * gapPenalty
    for i in range(1,ls):
        sa = s[i-1]
        for j in range(1,lt):
            ta = t[j-1]
            scoreVal = score[syms[sa]][syms[ta]]
            a = mat[i-1][j] + gapPenalty
            b = mat[i][j-1] + gapPenalty
            c = mat[i-1][j-1] + scoreVal
            mat[i][j] = max(a, b, c)
            if mat[i][j] == c:
                back[i][j] = 2
            elif mat[i][j] == b:
                back[i][j] = 1
            else:
                back[i][j] = 0
    (s1, t1) = backtrack(back, s, t, ls-1, lt-1)
    return (mat[-1][-1], s1, t1)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    s = stripLine(fp.readline())
    t = stripLine(fp.readline())
    fp.close()
    sys.setrecursionlimit(10000)
    (score_, s1, t1) = editDistance(s, t)
    print score_
    print s1
    print t1
