import sys
from common import factorial

def _printSignedPerm(front, n):
    for i in range(0,2**n):
        for j in range(0,n):
            if (i & (1 << j)) != 0:
                mult = 1
            else:
                mult = -1
            print (front[j]*mult),
        print

def _perm(front, plist, n):
    if len(plist) <= 0:
        _printSignedPerm(front, n)
        front = []
        return
    for elem in plist:
        front.append(elem)
        tmp = list(plist)
        tmp.remove(elem)
        _perm(front, tmp, n)
        front.remove(elem)

def signedPerm(n):
    print (factorial(n) * 2**n)
    plist = range(1,n+1)
    _perm([], plist, n)

if __name__ == '__main__':
    n = int(sys.argv[1])
    signedPerm(n)
