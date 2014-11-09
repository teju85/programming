import sys
from common import patt2num, stripLine

def allKmers(text, k, symMap):
    out = []
    for i in range(0,len(text)-k+1):
        t = text[i:i+k]
        n = patt2num(t, symMap)
        out.append((n, t))
    out = sorted(out)
    return out

if __name__ == '__main__':
    symMap = {'A':0, 'C':1, 'G':2, 'T':3}
    fp = open(sys.argv[1], 'r')
    k = int(fp.readline())
    text = stripLine(fp.readline())
    fp.close()
    kmers = allKmers(text, k, symMap)
    for i in kmers:
        print i[1]
