import sys
from common import readFasta, patt2num

def kmerComp(dna, k):
    symMap = {'A':0, 'C':1, 'G':2, 'T':3}
    comp = {}
    for i in range(0,4**k):
        comp[i] = 0
    for i in range(0,len(dna)-k+1):
        patt = dna[i:i+k]
        comp[patt2num(patt, symMap)] += 1
    return comp

if __name__ == '__main__':
    dna = readFasta(sys.argv[1])[0][1]
    comp = kmerComp(dna, 4)
    for c in comp.keys():
        print comp[c],
    print
