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
    [ 2, -2,  0,  0, -3,  1, -1, -1, -1, -2, -1,  0,  1,  0, -2,  1,  1,  0, -6, -3],
    [-2, 12, -5, -5, -4, -3, -3, -2, -5, -6, -5, -4, -3, -5, -4,  0, -2, -2, -8,  0],
    [ 0, -5,  4,  3, -6,  1,  1, -2,  0, -4, -3,  2, -1,  2, -1,  0,  0, -2, -7, -4],
    [ 0, -5,  3,  4, -5,  0,  1, -2,  0, -3, -2,  1, -1,  2, -1,  0,  0, -2, -7, -4],
    [-3, -4, -6, -5,  9, -5, -2,  1, -5,  2,  0, -3, -5, -5, -4, -3, -3, -1,  0,  7],
    [ 1, -3,  1,  0, -5,  5, -2, -3, -2, -4, -3,  0,  0, -1, -3,  1,  0, -1, -7, -5],
    [-1, -3,  1,  1, -2, -2,  6, -2,  0, -2, -2,  2,  0,  3,  2, -1, -1, -2, -3,  0],
    [-1, -2, -2, -2,  1, -3, -2,  5, -2,  2,  2, -2, -2, -2, -2, -1,  0,  4, -5, -1],
    [-1, -5,  0,  0, -5, -2,  0, -2,  5, -3,  0,  1, -1,  1,  3,  0,  0, -2, -3, -4],
    [-2, -6, -4, -3,  2, -4, -2,  2, -3,  6,  4, -3, -3, -2, -3, -3, -2,  2, -2, -1],
    [-1, -5, -3, -2,  0, -3, -2,  2,  0,  4,  6, -2, -2, -1,  0, -2, -1,  2, -4, -2],
    [ 0, -4,  2,  1, -3,  0,  2, -2,  1, -3, -2,  2,  0,  1,  0,  1,  0, -2, -4, -2],
    [ 1, -3, -1, -1, -5,  0,  0, -2, -1, -3, -2,  0,  6,  0,  0,  1,  0, -1, -6, -5],
    [ 0, -5,  2,  2, -5, -1,  3, -2,  1, -2, -1,  1,  0,  4,  1, -1, -1, -2, -5, -4],
    [-2, -4, -1, -1, -4, -3,  2, -2,  3, -3,  0,  0,  0,  1,  6,  0, -1, -2,  2, -4],
    [ 1,  0,  0,  0, -3,  1, -1, -1,  0, -3, -2,  1,  1, -1,  0,  2,  1, -1, -2, -3],
    [ 1, -2,  0,  0, -3,  0, -1,  0,  0, -2, -1,  0,  0, -1, -1,  1,  3,  0, -5, -3],
    [ 0, -2, -2, -2, -1, -1, -2,  4, -2,  2,  2, -2, -1, -2, -2, -1,  0,  4, -6, -2],
    [-6, -8, -7, -7,  0, -7, -3, -5, -3, -2, -4, -4, -6, -5,  2, -2, -5, -6, 17,  0],
    [-3,  0, -4, -4,  7, -5,  0, -1, -4, -1, -2, -2, -5, -4, -4, -3, -3, -2,  0, 10],
]

gapPenalty = -5

def findLocalAlignment(s, t, L):
    (maxI, maxJ) = (0, 0)
    maxVal = -1
    for i in range(0,len(L)):
        for j in range(0,len(L[0])):
            if L[i][j] > maxVal:
                maxVal = L[i][j]
                (maxI, maxJ) = (i, j)
    (i, j) = (maxI, maxJ)
    while L[i-1][j-1] != 0:
        maxi = max(L[i][j-1], L[i-1][j-1], L[i-1][j])
        if maxi == L[i][j-1]:
            j -= 1
        elif maxi == L[i-1][j-1]:
            i -= 1
            j -= 1
        else:
            i -= 1
    return (maxVal, s[i-1:maxI], t[j-1:maxJ])

def localAlignment(s, t):
    ls = len(s) + 1
    lt = len(t) + 1
    L = [ [0 for j in range(0,lt)]  for i in range(0,ls)]
    E = [ [0 for j in range(0,lt)]  for i in range(0,ls)]
    F = [ [0 for j in range(0,lt)]  for i in range(0,ls)]
    for i in range(1,ls):
        sa = s[i-1]
        for j in range(1,lt):
            ta = t[j-1]
            scoreVal = score[syms[sa]][syms[ta]]
            E[i][j] = max((L[i][j-1]+gapPenalty), (E[i][j-1]+gapPenalty))
            F[i][j] = max((L[i-1][j]+gapPenalty), (F[i-1][j]+gapPenalty))
            L[i][j] = max(0, E[i][j], (L[i-1][j-1]+scoreVal), F[i][j])
    return findLocalAlignment(s, t, L)

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
    sys.setrecursionlimit(20000)
    fp = open(sys.argv[1], 'r')
    s = stripLine(fp.readline())
    t = stripLine(fp.readline())
    fp.close()
    (score1, s1, t1) = localAlignment(s, t)
    (score2, s2, t2) = editDistance(s1, t1)
    print score2
    print s2
    print t2
