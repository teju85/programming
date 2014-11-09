import sys
from common import factorial

def _perm(front, plist):
    if len(plist) <= 0:
        for f in front:
            print f,
        print
        front = []
        return
    for elem in plist:
        front.append(elem)
        tmp = list(plist)
        tmp.remove(elem)
        _perm(front, tmp)
        front.remove(elem)

def perm(n):
    print factorial(n)
    plist = range(1,n+1)
    _perm([], plist)

if __name__ == '__main__':
    n = int(sys.argv[1])
    perm(n)
