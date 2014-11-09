import sys
import string
from common import readFasta, lcsm

def removeSmaller(strs):
    maxLen = 0
    for s in strs:
        l = len(s)
        if l > maxLen:
            maxLen = l
    out = []
    for s in strs:
        if maxLen == len(s):
            out.append(s)
    return out

if __name__ == '__main__':
    dnas = readFasta(sys.argv[1])
    num = len(dnas)
    subStrs = [dnas[0][1]]
    for i in range(1,num):
        sub = []
        for s in subStrs:
            sub += lcsm(s, dnas[i][1])
        subStrs = removeSmaller(sub)
    print subStrs
