import sys
from common import stripLine

def numBreakPoints(arr):
    num = 2   # begin and end
    for i in range(0,len(arr)-1):
        delta = arr[i+1] - arr[i]
        if delta < -1  or  delta > 1:
            num += 1
            print arr[i+1], arr[i], i
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
