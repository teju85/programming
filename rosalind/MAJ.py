import sys
from common import readArrayFromLine, readIntPair

def major(arr):
    m = {}
    for a in arr:
        if a not in m:
            m[a] = 0
        m[a] += 1
    limit = len(arr) / 2
    for k in m.keys():
        if m[k] > limit:
            return k
    return -1

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    (k, n) = readIntPair(fp)
    arr = []
    for i in range(0,k):
        arr.append(readArrayFromLine(fp))
    fp.close()
    for a in arr:
        print major(a),
    print
