import sys
import re
from common import readLine, stripLine

def printPos(Text, patts):
    pos = []
    for patt in patts:
        regex = re.compile(patt)
        start = 0
        while True:
            match = regex.search(Text, start)
            if match is None:
                break
            start = match.start() + 1
            pos.append(match.start())
    pos = sorted(pos)
    for p in pos:
        print p,
    print

if __name__ == '__main__':
    fp = open(sys.argv[1])
    Text = readLine(fp)
    patts = []
    for line in fp.readlines():
        patts.append(stripLine(line))
    fp.close()
    printPos(Text, patts)
