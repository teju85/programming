import sys
import string
from common import readFasta, dna2prot, getDnaCodonTable

def removeIntronsFrom(dna, introns):
    out = dna[1]
    print out
    for intron in introns:
        out = out.replace(intron[1], "")
    table = getDnaCodonTable()
    return dna2prot(out, table)

if __name__ == '__main__':
    dnas = readFasta(sys.argv[1])
    print removeIntronsFrom(dnas[0], dnas[1:])
