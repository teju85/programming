import sys
from common import stripLine
import string

def positions(text, patt):
    out = []
    pos = -1
    while True:
        pos = string.find(text, patt, pos+1)
        if pos < 0:
            break
        out.append(pos)
    return out

def allPositions(text, patts):
    out = []
    for p in patts:
        out += positions(text, p)
    out = sorted(out)
    return out

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    text = stripLine(fp.readline())
    patts = []
    for line in fp.readlines():
        patts.append(stripLine(line))
    fp.close()
    pos = allPositions(text, patts)
    for p in pos:
        print p,
    print
