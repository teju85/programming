import sys
from common import readIntPair, stripLine

def generateMismatches(s, d):
    uniq = set()
    if d <= 0:
        uniq.add(s)
        return uniq
    for i in range(0,len(s)):
        for g in 'ACGT':
            t = s[:i] + g + s[i+1:]
            tmp = generateMismatches(t, d-1)
            uniq.update(tmp)
    return uniq

def generateKeys(dnaString, k, d):
    subs = set()
    for idx in range(0,len(dnaString)-k+1):
        subDna = dnaString[idx:idx+k]
        subs.update(generateMismatches(subDna, d))
    return subs

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    dnas = []
    (k, d) = readIntPair(fp)
    for line in fp.readlines():
        dnas.append(stripLine(line))
    fp.close()
    motifs = None
    for dna in dnas:
        m = generateKeys(dna, k, d)
        if motifs is None:
            motifs = m
        else:
            motifs = motifs.intersection(m)
    for m in motifs:
        print m,
    print
