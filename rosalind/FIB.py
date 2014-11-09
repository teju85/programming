import sys

def wabbits(n, k):
    if n <= 0:
        return 0
    if n <= 2:
        return 1
    fn1 = fn2 = 1
    for idx in range(3, n+1):
        fni = (k * fn1) + fn2
        fn1 = fn2
        fn2 = fni
    return fn2

if __name__ == '__main__':
    n = int(sys.argv[1])
    k = int(sys.argv[2])
    print wabbits(n, k)
