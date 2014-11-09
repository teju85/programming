import sys

if __name__ == '__main__':
    n = int(sys.argv[1])
    k = int(sys.argv[2])
    pnk = 1
    for i in range(n,n-k,-1):
        pnk *= i
        pnk %= 1000000
    print pnk
