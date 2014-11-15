import sys
from common import stripLine

def suffixOverlap(x, y):
    k = len(x) - 1
    if x[1:] == y[0:k]:
        return True
    return False

def overlapGraph(dnas):
    for i in range(0,len(dnas)):
        for j in range(0,len(dnas)):
            if i == j:
                continue
            if suffixOverlap(dnas[i], dnas[j]):
                print '%s -> %s' % (dnas[i], dnas[j])

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    dnas = []
    for line in fp.readlines():
        dnas.append(stripLine(line))
    fp.close()
    overlapGraph(dnas)
