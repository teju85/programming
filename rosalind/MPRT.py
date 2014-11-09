import sys
import re
from common import readFastaFromUniProt, stripLine

def printPositions(inFile):
    regex = re.compile(r'N[^P][ST][^P]')
    fp = open(inFile, 'r')
    for line in fp.readlines():
        line = stripLine(line)
        dna = readFastaFromUniProt(line)[0][1]
        idx = []
        pos = 0
        match = ''
        while True:
            match = regex.search(dna, pos)
            if match is None:
                break
            pos = match.start() + 1
            idx.append(pos)
        if len(idx) <= 0:
            continue
        print line
        for m in idx:
            print m,
        print
    fp.close()

if __name__ == '__main__':
    printPositions(sys.argv[1])
