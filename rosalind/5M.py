import sys
from common import stripLine

def backtrack(back, s, t, u, i, j, k):
    if i <= 0 or j <= 0 or k <= 0:
        maxi = max(i, j, k)
        if i <= 0:
            s1 = '-'*maxi
        else:
            s1 = '-'*(maxi-i) + s[0:i]
        if j <= 0:
            t1 = '-'*maxi
        else:
            t1 = '-'*(maxi-j) + t[0:j]
        if k <= 0:
            u1 = '-'*maxi
        else:
            u1 = '-'*(maxi-k) + u[0:k]
        return (s1, t1, u1)
    direction = back[i][j][k]
    ipos = (direction / 4) % 2
    jpos = (direction / 2) % 2
    kpos = (direction) % 2
    (s1, t1, u1) = backtrack(back, s, t, u, i-ipos, j-jpos, k-kpos)
    if ipos == 0:
        s1 += '-'
    else:
        s1 += s[i-ipos]
    if jpos == 0:
        t1 += '-'
    else:
        t1 += t[j-jpos]
    if kpos == 0:
        u1 += '-'
    else:
        u1 += u[k-kpos]
    return (s1, t1, u1)

def workOnElement(mat, back, i, j, k, scoreVal):
    maxi = -sys.maxint
    maxIdx = -1
    for idx in range(1,8):
        ipos = (idx / 4) % 2
        jpos = (idx / 2) % 2
        kpos = (idx) % 2
        tmp = mat[i-ipos][j-jpos][k-kpos]
        if idx == 7:
            tmp += scoreVal
        if maxi < tmp:
            maxi = tmp
            maxIdx = idx
    mat[i][j][k] = maxi
    back[i][j][k] = maxIdx

def editDistance(s, t, u):
    ls = len(s) + 1
    lt = len(t) + 1
    lu = len(u) + 1
    mat = [ [ [0  for k in range(0,lu)]  for j in range(0,lt)]  for i in range(0,ls)]
    back = [ [ [-1 for k in range(0,lu)] for j in range(0,lt)]  for i in range(0,ls)]
    for i in range(1,ls):
        sa = s[i-1]
        for j in range(1,lt):
            ta = t[j-1]
            for k in range(1,lu):
                ua = u[k-1]
                scoreVal = 0
                if sa == ta and ta == ua:
                    scoreVal = 1
                workOnElement(mat, back, i, j, k, scoreVal)
    (s1, t1, u1) = backtrack(back, s, t, u, ls-1, lt-1, lu-1)
    return (mat[-1][-1][-1], s1, t1, u1)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    s = stripLine(fp.readline())
    t = stripLine(fp.readline())
    u = stripLine(fp.readline())
    fp.close()
    sys.setrecursionlimit(10000)
    (score_, s1, t1, u1) = editDistance(s, t, u)
    print score_
    print s1
    print t1
    print u1
