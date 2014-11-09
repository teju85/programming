import sys
from common import stripLine

def readSetFromLine(fp):
    out = set()
    line = stripLine(fp.readline())
    line = line.strip('{')
    line = line.strip('}')
    ss = line.split(', ')
    for s in ss:
        out.add(int(s))
    return out

def printSet(a):
    s = ', '.join(str(x) for x in a)
    print "{%s}" % s

def complement(a, num):
    out = set()
    for i in range(1,num+1):
        if i not in a:
            out.add(i)
    return out

def printAll(a, b, num):
    out = []
    out.append(a.union(b))
    out.append(a.intersection(b))
    out.append(a.difference(b))
    out.append(b.difference(a))
    out.append(complement(a, num))
    out.append(complement(b, num))
    for o in out:
        printSet(o)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    num = int(fp.readline())
    a = readSetFromLine(fp)
    b = readSetFromLine(fp)
    fp.close()
    printAll(a, b, num)
