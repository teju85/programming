import sys
from common import readIntPair, readArrayFromLine

def find2sum(arr):
    m = {}
    i = 1
    for a in arr:
        if -a in m:
            return (m[-a], i)
        m[a] = i
        i += 1
    return (-1, -1)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    (k, n) = readIntPair(fp)
    arr = []
    for i in range(0, k):
        arr.append(readArrayFromLine(fp))
    fp.close()
    for a in arr:
        (p, q) = find2sum(a)
        if p != -1:
            print p, q
        else:
            print -1
