import sys
from common import readArrayFromLine

def mergeSorted(a, b):
    i = 0
    j = 0
    la = len(a)
    lb = len(b)
    out = []
    while i < la and j < lb:
        if a[i] < b[j]:
            out.append(a[i])
            i += 1
        else:
            out.append(b[j])
            j += 1
    for t in range(i,la):
        out.append(a[t])
    for t in range(j,lb):
        out.append(b[t])
    return out

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    line = fp.readline()
    m = int(line)
    a = readArrayFromLine(fp)
    line = fp.readline()
    n = int(line)
    b = readArrayFromLine(fp)
    fp.close()
    out = mergeSorted(a, b)
    for t in out:
        print t,
    print
