import sys
from common import stripLine, deBruijn

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    dnas = []
    for line in fp.readlines():
        dnas.append(stripLine(line))
    fp.close()
    adj = deBruijn(dnas)
    for a in adj:
        print "(%s, %s)" % (a[0], a[1])
