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

gapOpening = -11
gapExtension = -1

STAY_MID   = 0
STAY_LOW   = 1
STAY_UP    = 2
MID_TO_LOW = 3
LOW_TO_MID = 4
MID_TO_UP  = 5
UP_TO_MID  = 6

def backtrack(back, backM, backL, backU, s, t, i, j):
    # TBD: this section is wrong!
    # need to handle this properly
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
    if direction == STAY_MID:
        back = backM
        (s1, t1) = backtrack(back, backM, backL, backU, s, t, i-1, j-1)
        s1 += s[i-1]
        t1 += t[j-1]
    elif direction == STAY_LOW:
        back = backL
        (s1, t1) = backtrack(back, backM, backL, backU, s, t, i-1, j)
        s1 += s[i-1]
        t1 += '-'
    elif direction == STAY_UP:
        back = backU
        (s1, t1) = backtrack(back, backM, backL, backU, s, t, i, j-1)
        s1 += '-'
        t1 += t[j-1]
    elif direction == MID_TO_LOW:
        back = backM
        (s1, t1) = backtrack(back, backM, backL, backU, s, t, i-1, j)
        s1 += s[i-1]
        t1 += '-'
    elif direction == LOW_TO_MID:
        back = backL
        (s1, t1) = backtrack(back, backM, backL, backU, s, t, i, j)
    elif direction == MID_TO_UP:
        back = backM
        (s1, t1) = backtrack(back, backM, backL, backU, s, t, i, j-1)
        s1 += '-'
        t1 += t[j-1]
    else:
        back = UP_TO_MID
        back = backU
        (s1, t1) = backtrack(back, backM, backL, backU, s, t, i, j)
    return (s1, t1)

def editDistance(s, t):
    ls = len(s) + 1
    lt = len(t) + 1
    low = [ [0 for j in range(0,lt)]  for i in range(0,ls)]
    up  = [ [0 for j in range(0,lt)]  for i in range(0,ls)]
    mid = [ [0 for j in range(0,lt)]  for i in range(0,ls)]
    backL = [ [-1 for j in range(0,lt)]  for i in range(0,ls)]
    backU = [ [-1 for j in range(0,lt)]  for i in range(0,ls)]
    backM = [ [-1 for j in range(0,lt)]  for i in range(0,ls)]
    low[1][0] = gapOpening
    mid[1][0] = gapOpening
    for i in range(2,ls):
        low[i][0] = low[i-1][0] + gapExtension
        mid[i][0] = mid[i-1][0] + gapExtension
    up[0][1] = gapOpening
    mid[0][1] = gapOpening
    for j in range(2, lt):
        up[0][j] = up[0][j-1] + gapExtension
        mid[0][j] = mid[0][j-1] + gapExtension
    for i in range(1,ls):
        sa = s[i-1]
        for j in range(1,lt):
            ta = t[j-1]
            scoreVal = score[syms[sa]][syms[ta]]
            a = low[i-1][j]+gapExtension
            b = mid[i-1][j]+gapOpening
            low[i][j] = max(a, b)
            if low[i][j] == a:
                backL[i][j] = STAY_LOW
            else:
                backL[i][j] = MID_TO_LOW
            a = up[i][j-1]+gapExtension
            b = mid[i][j-1]+gapOpening
            up[i][j] = max(a, b)
            if up[i][j] == a:
                backU[i][j] = STAY_UP
            else:
                backU[i][j] = MID_TO_UP
            a = low[i][j]
            b = up[i][j]
            c = mid[i-1][j-1] + scoreVal
            mid[i][j] = max(a, b, c)
            if mid[i][j] == c:
                backM[i][j] = STAY_MID
            elif mid[i][j] == b:
                backM[i][j] = UP_TO_MID
            else:
                backM[i][j] = LOW_TO_MID
    back = backM
    (s1, t1) = backtrack(back, backM, backL, backU, s, t, ls-1, lt-1)
    return (mid[-1][-1], s1, t1)

if __name__ == '__main__':
    sys.setrecursionlimit(20000)
    fp = open(sys.argv[1], 'r')
    s = stripLine(fp.readline())
    t = stripLine(fp.readline())
    fp.close()
    (score1, s1, t1) = editDistance(s, t)
    print score1
    print s1
    print t1
