import sys
from common import readLine

def approxMatches(patt, text, d):
    out = []
    lp = len(patt)
    lt = len(text) - lp
    for i in range(0,lt+1):
        num = 0
        for j in range(0,lp):
            if text[i+j] != patt[j]:
                num += 1
            if num > d:
                break
        if num <= d:
            out.append(i)
    return out

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    patt = readLine(fp)
    text = readLine(fp)
    d = int(fp.readline())
    fp.close()
    pos = approxMatches(patt, text, d)
    for p in pos:
        print p,
    print
