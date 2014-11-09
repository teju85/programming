import sys

def n2p(num, lp, syms, base):
    p = ''
    for i in range(0,lp):
        p = syms[num%base] + p
        num /= base
    return p

def lex(syms, n):
    base = len(syms)
    for num in range(0,base**n):
        print n2p(num, n, syms, base)

if __name__ == '__main__':
    syms = sys.argv[1].split(' ')
    n = int(sys.argv[2])
    lex(syms, n)
