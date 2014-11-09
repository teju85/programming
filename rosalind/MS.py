import sys
from common import readArrayFromLine

def mergeSorted(a, b):
    i = 0
    j = 0
    la = len(a)
    lb = len(b)
    out = []
    while i < la and j < lb:
        if a[i] < b[j]:
            out.append(a[i])
            i += 1
        else:
            out.append(b[j])
            j += 1
    for t in range(i,la):
        out.append(a[t])
    for t in range(j,lb):
        out.append(b[t])
    return out

def mergeSort(arr):
    la = len(arr)
    if la == 1:
        return arr
    la2 = la / 2
    a1 = mergeSort(arr[0:la2])
    a2 = mergeSort(arr[la2:])
    out = mergeSorted(a1, a2)
    return out

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    n = int(fp.readline())
    arr = readArrayFromLine(fp)
    fp.close()
    out = mergeSort(arr)
    for a in out:
        print a,
    print
