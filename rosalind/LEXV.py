import sys
from common import patt2num

def n2p(num, lp, syms, base):
    p = ''
    for i in range(0,lp):
        p = syms[num%base] + p
        num /= base
    return p

def lex(syms, n):
    out = []
    base = len(syms)
    for num in range(0,base**n):
        out.append(n2p(num, n, syms, base))
    return out

def allLex(syms, n):
    out = []
    for i in range(1,n+1):
        out += lex(syms, i)
    return out

symMap = {}

def compare(a, b):
    if len(a) < len(b):
        small = a
        large = b[0:len(a)]
        na = patt2num(small, symMap)
        nb = patt2num(large, symMap)
        if na <= nb:
            return -1
        else:
            return 1
    elif len(a) == len(b):
        na = patt2num(a, symMap)
        nb = patt2num(b, symMap)
        if na < nb:
            return -1
        elif na == nb:
            return 0
        else:
            return 1
    else:
        return (-1 * compare(b, a))

if __name__ == '__main__':
    syms = sys.argv[1].split(' ')
    n = int(sys.argv[2])
    global symMap
    symMap = {}
    for i in range(0,len(syms)):
        symMap[syms[i]] = i
    words = allLex(syms, n)
    words = sorted(words, cmp=compare)
    for w in words:
        print w
