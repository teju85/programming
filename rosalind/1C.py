import sys
import re

def printAllPos(patt, gene):
    regex = re.compile(patt)
    pos = 0
    while True:
        match = regex.search(gene, pos)
        if match is None:
            break
        print match.start(),
        pos = match.start() + 1
    print

if __name__ == '__main__':
    patt = sys.argv[1]
    gene = sys.argv[2]
    printAllPos(patt, gene)
