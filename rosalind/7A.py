import sys
from common import stripLine, generateTrie

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    strings = []
    for line in fp.readlines():
        strings.append(stripLine(line))
    fp.close()
    adjList = generateTrie(strings)
    for a in adjList:
        print a[0], a[1], a[2]
