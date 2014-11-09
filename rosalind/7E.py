import sys
from common import readLine

def lcsm(a, b):
    la = len(a) + 1
    lb = len(b) + 1
    mat = [[0 for x in range(0,lb)] for x in range(0,la)]
    subStrs = ''
    maxLen = 0
    cnt = 0
    for i in range(1,la):
        cnt += 1
        if cnt % 500 == 0:
            print cnt
        ca = a[i-1]
        for j in range(1,lb):
            cb = b[j-1]
            if ca == cb:
                mat[i][j] = mat[i-1][j-1] + 1
                if mat[i][j] > maxLen:
                    maxLen = mat[i][j]
                    #subStrs = []
                    #subStrs.append(a[i-maxLen:i])
                    subStrs = a[i-maxLen:i]
                #elif mat[i][j] == maxLen:
                #    subStrs.append(a[i-maxLen:i])
            else:
                mat[i][j] = 0
    return subStrs

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    t1 = readLine(fp)
    t2 = readLine(fp)
    fp.close()
    sub = lcsm(t1, t2)
    print sub
    #for s in sub:
    #    print s,
    #print
