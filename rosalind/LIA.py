import sys

def nci(n, i):
    prod = 1.0
    for t in range(n-i+1,n+1):
        prod *= t
    for t in range(1,i+1):
        prod /= t
    return prod

def atLeastN(k, N):
    prob = 0.0
    num = 1 << k
    for i in range(N,num+1):
        prob += nci(num,i) * (0.25**i) * (0.75**(num-i))
    return prob

if __name__ == '__main__':
    k = int(sys.argv[1])
    N = int(sys.argv[2])
    print atLeastN(k, N)
