import sys
from common import readArrayFromLine, readIntPair

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    (n, m) = readIntPair(fp)
    down = []
    for i in range(0,n):
        down.append(readArrayFromLine(fp))
    fp.readline()
    right = []
    for i in range(0,n+1):
        right.append(readArrayFromLine(fp))
    fp.close()
    mat = [ [0 for j in range(0,m+1)]  for i in range(0,n+1)]
    for j in range(0,m):
        mat[0][j+1] = mat[0][j] + right[0][j]
    for i in range(0,n):
        mat[i+1][0] = mat[i][0] + down[i][0]
    for i in range(1,n+1):
        for j in range(1,m+1):
            mat[i][j] = max(mat[i-1][j]+down[i-1][j] , mat[i][j-1]+right[i][j-1])
    print mat[n][m]
