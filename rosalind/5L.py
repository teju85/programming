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

def editDistanceLinear(s, t):
    ls = len(s) + 1
    lt = len(t) + 1
    prev = [0 for i in range(0,ls)]
    curr = [0 for i in range(0,ls)]
    for i in range(1,ls):
        prev[i] = i * gapPenalty
    for j in range(1,lt):
        ta = t[j-1]
        curr[0] = j * gapPenalty
        for i in range(1,ls):
            sa = s[i-1]
            scoreVal = score[syms[sa]][syms[ta]]
            a = curr[i-1] + gapPenalty
            b = prev[i] + gapPenalty
            c = prev[i-1] + scoreVal
            curr[i] = max(a, b, c)
        tmp = prev
        prev = curr
        curr = tmp
    return (curr, prev)

def findNextVertex(maxPos, ltMid, prevS, currS, s, t):
    sa = s[len(s)-maxPos]
    ta = t[len(t)-ltMid]
    symsa = syms[sa]
    symta = syms[ta]
    scoreVal = score[symsa][symta]
    a = prevS[maxPos] + gapPenalty
    b = currS[maxPos+1] + gapPenalty
    c = prevS[maxPos+1] + scoreVal
    ma = max(a, b, c)
    nextCol = ltMid
    nextRow = maxPos
    if ma == c:
        nextRow += 1
        nextCol += 1
    elif ma == b:
        nextRow += 1
    else:
        nextCol += 1
    return (nextRow, nextCol)

def middleEdge(s, t):
    ltMid = len(t) / 2
    (prevF, currF) = editDistanceLinear(s, t[0:ltMid])
    t1 = t[ltMid:]
    (prevS, currS) = editDistanceLinear(s[::-1], t1[::-1])
    prevS.reverse()
    currS.reverse()
    maxVal = -sys.maxint
    maxPos = -1
    for i in range(0,len(s)+1):
        length = currF[i] + currS[i]
        if maxVal < length:
            maxVal = length
            maxPos = i
    if maxPos == 0  or  maxPos == len(s):
        (nextRow, nextCol) = (maxPos, ltMid+1)
    else:
        (nextRow, nextCol) = findNextVertex(maxPos, ltMid, prevS, currS, s, t)
    return (maxPos, ltMid, nextRow, nextCol)

def linearSpace(s, t):
    if len(t) <= 0:
        return (s, len(s)*'-')
    if len(s) <= 0:
        return (len(t)*'-', t)
    if len(t) == 1  and  len(s) == 1:
        return (s, t)
    (row1, col1, row2, col2) = middleEdge(s, t)
    row1 -= 1
    col1 -= 1
    row2 -= 1
    col2 -= 1
    if row1 >= 0  and  col1 >= 0:
        (prevS, prevT) = linearSpace(s[0:row1], t[0:col1])
    else:
        (prevS, prevT) = ('', '')
    if row2 >= 0  and  col2 >= 0:
        (nextS, nextT) = linearSpace(s[row2:], t[col2:])
    else:
        (nextS, nextT) = ('', '')
    if row1 == row2:
        sa = '-'
    else:
        sa = s[row2-1]
    if col1 == col2:
        ta = '-'
    else:
        ta = t[col2-1]
    return (prevS+sa+nextS, prevT+ta+nextT)

def evalScore(s, t):
    sc = 0
    for i in range(0,len(s)):
        if s[i] == '-':
            sc += gapPenalty
        elif t[i] == '-':
            sc += gapPenalty
        else:
            sc += score[syms[s[i]]][syms[t[i]]]
    return sc

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    s = stripLine(fp.readline())
    t = stripLine(fp.readline())
    fp.close()
    (sa, ta) = linearSpace(s, t)
    print evalScore(sa, ta)
    print sa
    print ta
