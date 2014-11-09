import sys
from common import readArrayFromLine

def partition(arr):
    s = 0
    e = len(arr) - 1
    first = s
    last = e
    pivot = arr[s]
    out = [-1 for i in range(s,e+1)]
    for i in range(s,e+1):
        if arr[i] < pivot:
            out[first] = arr[i]
            first += 1
        elif arr[i] > pivot:
            out[last] = arr[i]
            last -= 1
    for i in range(first,last+1):
        out[i] = pivot
    return (out, first, last)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    n = int(fp.readline())
    arr = readArrayFromLine(fp)
    fp.close()
    (out, q, r) = partition(arr)
    print q, r
    for a in out:
        print a,
    print
