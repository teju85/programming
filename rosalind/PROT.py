import sys
from common import getRnaCodonTable, rna2prot

def protein(mrna):
    table = getRnaCodonTable()
    return rna2prot(mrna, table)

if __name__ == '__main__':
    print protein(sys.argv[1])
