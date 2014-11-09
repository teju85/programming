import sys
from common import stripLine

comp = {}
comp['A'] = 'U'
comp['U'] = 'A'
comp['C'] = 'G'
comp['G'] = 'C'

wobbleComp = {}
wobbleComp['U'] = 'G'
wobbleComp['G'] = 'U'
wobbleComp['A'] = '-'
wobbleComp['C'] = '-'

nearby = 4

wobbleMap = {}

def wobble(dna):
    if len(dna) < nearby:
        return 1
    if dna in wobbleMap:
        return wobbleMap[dna]
    num = wobble(dna[1:])
    for k in range(nearby,len(dna)):
        if dna[0] == comp[dna[k]]:
            num += wobble(dna[1:k]) * wobble(dna[k+1:])
        if dna[0] == wobbleComp[dna[k]]:
            num += wobble(dna[1:k]) * wobble(dna[k+1:])
    wobbleMap[dna] = num
    #print num, dna
    return num

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    dna = stripLine(fp.readline())
    fp.close()
    print wobble(dna)
