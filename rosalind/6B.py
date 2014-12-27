import sys
from common import stripLine

def numBreakPoints(arr):
    tmp = [0]
    tmp += arr
    tmp.append(len(arr)+1)
    num = 0
    for i in range(0,len(tmp)-1):
        if (tmp[i+1] - tmp[i]) != 1:
            num += 1
    return num

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    line = stripLine(fp.readline())
    line = line.strip('(')
    line = line.strip(')')
    fp.close()
    arr = line.split(' ')
    arr = map(int, arr)
    print numBreakPoints(arr)
