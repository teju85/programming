import sys
from common import readFasta
import string

# assumes UC counts are same as AG!
def getCountsAG(rna):
    a = string.count(rna, 'A')
    g = string.count(rna, 'G')
    return (a, g)

def getNumPerfectMatchings(rna):
    (ca, cg) = getCountsAG(rna)
    count = 1
    for i in range(2, ca+1):
        count *= i
    for i in range(2, cg+1):
        count *= i
    return count

if __name__ == '__main__':
    rna = readFasta(sys.argv[1])[0][1]
    print getNumPerfectMatchings(rna)
