import sys
import math

def comb(n, k):
    if k > (n / 2):
        return comb(n, n-k)
    prod = 1
    for i in range(n-k+1,n+1):
        prod *= i
    tmp = 1
    for i in range(2,k+1):
        tmp *= i
    return (prod / tmp)

def indc(n):
    n2 = 2 * n
    arr = [0.0   for i in range(0,n2)]
    delta = (n2 * math.log(0.5, 10))
    for i in range(0,n2):
        arr[i] = comb(n2, i+1)
    for i in range(n2-2,-1,-1):
        arr[i] += arr[i+1]
    for i in range(0,n2):
        arr[i] = math.log(arr[i], 10) + delta
    return arr

if __name__ == '__main__':
    n = int(sys.argv[1])
    arr = indc(n)
    for a in arr:
        print a,
    print
