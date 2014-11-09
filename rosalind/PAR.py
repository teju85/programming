import sys
from common import readArrayFromLine

def partition(arr, s, e):
    first = s
    pivot = arr[s]
    (arr[s], arr[e]) = (arr[e], arr[s])
    for i in range(s,e):
        if arr[i] <= pivot:
            (arr[first], arr[i]) = (arr[i], arr[first])
            first += 1
    (arr[first], arr[e]) = (arr[e], arr[first])
    return first

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    n = int(fp.readline())
    arr = readArrayFromLine(fp)
    fp.close()
    pivotPos = partition(arr, 0, len(arr)-1)
    for a in arr:
        print a,
    print
