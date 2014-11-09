import sys
from common import stripLine, revComp

def allSharedKmers(k, s1, s2):
    allKmers = {}
    for j in range(0,len(s2)-k+1):
        sub = s2[j:j+k]
        if sub not in allKmers:
            allKmers[sub] = []
        allKmers[sub].append(j)
    pairs = []
    for i in range(0,len(s1)-k+1):
        sub1 = s1[i:i+k]
        rcsub1 = revComp(sub1)
        if sub1 in allKmers:
            for j in allKmers[sub1]:
                pairs.append((i, j))
        if rcsub1 in allKmers:
            for j in allKmers[rcsub1]:
                pairs.append((i, j))
    return pairs

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    k = int(fp.readline())
    s1 = stripLine(fp.readline())
    s2 = stripLine(fp.readline())
    fp.close()
    pairs = allSharedKmers(k, s1, s2)
    for p in pairs:
        print p
