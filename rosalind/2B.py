import sys
import string
import re
from common import getDnaCodonTable, isStopCodon, isStartCodon, revComp

def getRevDnaCodonTable(table):
    rev = {}
    for k in table.keys():
        v = table[k]
        if v not in rev:
            rev[v] = []
        rev[v].append(k)
    return rev

def getProts(dna, table):
    prots = []
    for i in range(0,3):
        prot = ''
        pos = i
        for j in range(i,len(dna)-2,3):
            if isStopCodon(dna[j:j+3]):
                prots.append((prot, pos))
                prot = ''
                pos = j + 3
                continue
            prot += table[dna[j:j+3]]
        if prot != '':
            prots.append((prot, pos))
    return prots

def findAll(prots, peptide, dna, rev=False):
    pos = []
    size = len(peptide) * 3
    regex = re.compile(peptide)
    for p in prots:
        start = 0
        while True:
            match = regex.search(p[0], start)
            if match is None:
                break
            start = match.start() + 1
            pos.append(match.start() * 3 + p[1])
    for p in pos:
        if rev:
            print revComp(dna[p:p+size])
        else:
            print dna[p:p+size]

def protein(dna, peptide):
    table = getDnaCodonTable()
    rev = getRevDnaCodonTable(table)
    prots = getProts(dna, table)
    findAll(prots, peptide, dna)
    rprots = getProts(revComp(dna), table)
    findAll(rprots, peptide, revComp(dna), True)

if __name__ == '__main__':
    protein(sys.argv[1], sys.argv[2])
