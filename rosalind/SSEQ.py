import sys
from common import readFasta

def subSeqPos(s, t):
    pos = []
    j = 0
    for i in range(0,len(s)):
        if s[i] == t[j]:
            j += 1
            pos.append(i+1)
            if j >= len(t):
                break
    return pos

if __name__ == '__main__':
    dnas = readFasta(sys.argv[1])
    pos = subSeqPos(dnas[0][1], dnas[1][1])
    for p in pos:
        print p,
    print
