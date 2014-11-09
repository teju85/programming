import sys

def nckMod(n, k):
    out = 1
    for i in range(n,n-k,-1):
        out *= i
    for i in range(1,k+1):
        out /= i
    return out % 1000000

def countFixedSizeSubsets(n, m):
    summation = 0
    for k in range(m,n+1):
        summation += nckMod(n, k)
        summation %= 1000000
    return summation

if __name__ == '__main__':
    n = int(sys.argv[1])
    m = int(sys.argv[2])
    print countFixedSizeSubsets(n, m)
