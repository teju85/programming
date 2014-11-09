import sys
from common import readArrayFromLine

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    arr = readArrayFromLine(fp)
    fp.close()
    arr = sorted(arr, reverse=True)
    diffMap = {}
    for i in range(0,len(arr)):
        for j in range(i+1,len(arr)):
            d = arr[i] - arr[j]
            if d == 0:
                continue
            if d not in diffMap:
                diffMap[d] = 0
            diffMap[d] += 1
    diffHist = []
    for d in diffMap.keys():
        diffHist.append((diffMap[d], d))
    diffHist = sorted(diffHist,reverse=True)
    for d in diffHist:
        (rep, num) = d
        for r in range(0,rep):
            print num,
    print
