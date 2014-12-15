import sys
from common import stripLine

penalty = -2

def backtrack(back, s, t, i, j):
    if i <= 0 or j <= 0:
        return ('', '')
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
    #for i in range(1,ls):
    #    mat[i][0] = i * penalty
    #for j in range(1,lt):
    #    mat[0][j] = j * penalty
    for i in range(1,ls):
        sa = s[i-1]
        for j in range(1,lt):
            ta = t[j-1]
            if sa == ta:
                scoreVal = 1
            else:
                scoreVal = penalty
            a = mat[i-1][j] + penalty
            b = mat[i][j-1] + penalty
            c = mat[i-1][j-1] + scoreVal
            mat[i][j] = max(a, b, c)
            if mat[i][j] == c:
                back[i][j] = 2
            elif mat[i][j] == b:
                back[i][j] = 1
            else:
                back[i][j] = 0
    (maxI, maxJ) = (ls-1, 0)
    maxVal = -sys.maxint
    for j in range(lt-1,-1,-1):
        if mat[maxI][j] > maxVal:
            maxVal = mat[i][j]
            maxJ = j
    (i, j) = (maxI, maxJ)
    (s1, t1) = backtrack(back, s, t, maxI, maxJ)
    return (mat[maxI][maxJ], s1, t1)

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
