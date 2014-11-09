import sys
from common import stripLine

def suffixOverlap(x, y):
    for i in range(1,len(x)+1):
        if i > len(y):
            break
        if x[-i:] == y[0:i]:
            return True
    return False

def overlapGraph(dnas):
    for i in range(0,len(dnas)):
        for j in range(i+1,len(dnas)):
            if suffixOverlap(dnas[i], dnas[j]):
                print '%s -> %s' % (dnas[i], dnas[j])

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    dnas = []
    for line in fp.readlines():
        dnas.append(stripLine(line))
    fp.close()
    overlapGraph(dnas)
