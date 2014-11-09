import sys
from common import readArrayFromLine

def mergeSorted(a, b):
    i = 0
    j = 0
    la = len(a)
    lb = len(b)
    numInv = 0
    out = []
    while i < la and j < lb:
        if a[i] <= b[j]:
            out.append(a[i])
            i += 1
        else:
            out.append(b[j])
            numInv += (la - i)
            j += 1
    for t in range(i,la):
        out.append(a[t])
    for t in range(j,lb):
        out.append(b[t])
    return (numInv, out)

def mergeSort(arr):
    la = len(arr)
    if la == 1:
        return (0, arr)
    la2 = la / 2
    (i1, a1) = mergeSort(arr[0:la2])
    (i2, a2) = mergeSort(arr[la2:])
    (i3, out) = mergeSorted(a1, a2)
    numInv = i1 + i2 + i3
    return (numInv, out)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    n = int(fp.readline())
    arr = readArrayFromLine(fp)
    fp.close()
    (ni, out) = mergeSort(arr)
    print ni
