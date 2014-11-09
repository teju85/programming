import sys
from common import stripLine

def editDistance(a, b):
    la = len(a)
    lb = len(b)
    mat = [ [0  for i in range(0,la+1)]  for j in range(0,lb+1)]
    for i in range(1, lb+1):
        mat[i][0] = i
    for j in range(1, la+1):
        mat[0][j] = j
    for i in range(0,lb):
        for j in range(0,la):
            if b[i] == a[j]:
                mat[i+1][j+1] = mat[i][j]
            else:
                mm = min(mat[i][j], mat[i][j+1], mat[i+1][j])
                mat[i+1][j+1] = mm + 1
    return mat[lb][la]

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    a = stripLine(fp.readline())
    b = stripLine(fp.readline())
    fp.close()
    print editDistance(a, b)
