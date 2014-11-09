import sys
from common import readFasta
import string

def getCountsACGU(rna):
    a = string.count(rna, 'A')
    c = string.count(rna, 'C')
    g = string.count(rna, 'G')
    u = string.count(rna, 'U')
    return (a, c, g, u)

def npk(n, k):
    if k > n:
        (n, k) = (k, n)
    count = 1
    for i in range(n,n-k,-1):
        count *= i
    return count

def getNumMaximumMatchings(rna):
    (ca, cc, cg, cu) = getCountsACGU(rna)
    count = npk(ca, cu) * npk(cg, cc)
    return count

if __name__ == '__main__':
    rna = readFasta(sys.argv[1])[0][1]
    print getNumMaximumMatchings(rna)
