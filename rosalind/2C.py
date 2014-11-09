import sys
from common import stripLine

massTable = {
    'G' : 57,
    'A' : 71,
    'S' : 87,
    'P' : 97,
    'V' : 99,
    'T' : 101,
    'C' : 103,
    'I' : 113,
    'L' : 113,
    'N' : 114,
    'D' : 115,
    'K' : 128,
    'Q' : 128,
    'E' : 129,
    'M' : 131,
    'H' : 137,
    'F' : 147,
    'R' : 156,
    'Y' : 163,
    'W' : 186,
}

def calculateMass(subpep):
    mass = 0
    for s in subpep:
        mass += massTable[s]
    return mass

def cyclospectrum(peptide):
    out = [(0,'')]
    length = len(peptide)
    for k in range(1,length):
        for i in range(0,length-k+1):
            sub = peptide[i:i+k]
            out.append((calculateMass(sub), sub))
        for i in range(length-k+1,length):
            sub = peptide[i:length] + peptide[0:k-length+i]
            out.append((calculateMass(sub), sub))
    out.append((calculateMass(peptide), peptide))
    out = sorted(out)
    return out

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    peptide = stripLine(fp.readline())
    fp.close()
    out = cyclospectrum(peptide)
    for o in out:
        print o[0],
    print
