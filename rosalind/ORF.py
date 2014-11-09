import sys
import string
from common import readFasta, getDnaCodonTable, isStartCodon, dna2prot, revComp

def protein(dna):
    table = getDnaCodonTable()
    size = len(dna)
    prots = {}
    for i in range(0,size-3):
        if not isStartCodon(dna[i:i+3]):
            continue
        p = dna2prot(dna[i:], table)
        if p != '':
            prots[p] = 1
    revDna = revComp(dna)
    for i in range(0,size-3):
        if not isStartCodon(revDna[i:i+3]):
            continue
        p = dna2prot(revDna[i:], table)
        if p != '':
            prots[p] = 1
    for k in prots.keys():
        print k

if __name__ == '__main__':
    dna = readFasta(sys.argv[1])[0][1]
    protein(dna)
