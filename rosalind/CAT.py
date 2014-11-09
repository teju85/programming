import sys
from common import readFasta

comp = {}
comp['A'] = 'U'
comp['U'] = 'A'
comp['C'] = 'G'
comp['G'] = 'C'

catMap = {}

def catalan(dna):
    if len(dna) <= 1:
        return 1
    if dna in catMap:
        return catMap[dna]
    num = 0
    for k in range(1,len(dna),2):
        if dna[0] == comp[dna[k]]:
            num += catalan(dna[1:k]) * catalan(dna[k+1:])
            num %= 1000000
    catMap[dna] = num
    #print num, dna
    return num

if __name__ == '__main__':
    dna = readFasta(sys.argv[1])[0][1]
    print catalan(dna)
