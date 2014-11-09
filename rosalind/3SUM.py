import sys
from common import readIntPair, readArrayFromLine

def find3sum(arr):
    m = {}
    for i in range(0,len(arr)):
        if arr[i] not in m:
            m[arr[i]] = []
        m[arr[i]].append(i)
    for q in range(0,len(arr)):
        for r in range(q+1,len(arr)):
            val = -(arr[q] + arr[r])
            if val in m:
                for p in m[val]:
                    if p < q:
                        return (p+1, q+1, r+1)
    return (-1, -1, -1)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    (k, n) = readIntPair(fp)
    arr = []
    for i in range(0, k):
        arr.append(readArrayFromLine(fp))
    fp.close()
    for a in arr:
        (p, q, r) = find3sum(a)
        if p != -1:
            print p, q, r
        else:
            print -1
