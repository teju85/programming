import sys
from common import readArrayFromLine

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

def uniqWeights():
    w = set()
    for k in massTable.keys():
        w.add(massTable[k])
    return w

def generateSpectrum(s):
    spec = {0:1}
    pepMass = 0
    for k in range(1,len(s)+1):
        for i in range(0,len(s)-k+1):
            mass = 0
            for j in range(i,i+k):
                mass += s[j]
            if mass not in spec:
                spec[mass] = 0
            spec[mass] += 1
            if mass > pepMass:
                pepMass = mass
    return (spec, pepMass)

def generateCycloSpectrum(s):
    spec = {0:1}
    length = len(s)
    mass = 0
    for i in range(0,length):
        mass += s[i]
    if mass not in spec:
        spec[mass] = 0
    spec[mass] += 1
    for k in range(1,length):
        for i in range(0,length):
            mass = 0
            for j in range(i,i+k):
                if j >= length:
                    j -= length
                mass += s[j]
            if mass not in spec:
                spec[mass] = 0
            spec[mass] += 1
    return spec

def arr2spectrum(arr):
    spec = {}
    mass = 0
    for a in arr:
        if a not in spec:
            spec[a] = 0
        spec[a] += 1
        if a > mass:
            mass = a
    return (spec, mass)

def compareSpectrums(smaller, larger):
    for s in smaller.keys():
        if s not in larger:
            return False
        if smaller[s] > larger[s]:
            return False
    return True

def sameCycloSpectrums(pep, parent):
    smaller = generateCycloSpectrum(pep)
    if len(smaller) != len(parent):
        return False
    for s in smaller.keys():
        if s not in parent:
            return False
        if smaller[s] != parent[s]:
            return False
    return True

def branchBound(specs, uniq, parentMass, parentSpectrum, solutions):
    out = []
    for i in range(0,len(specs)):
        for u in uniq:
            tmp = specs[i] + [u]
            (s, mass) = generateSpectrum(tmp)
            if mass == parentMass:
                if sameCycloSpectrums(tmp, parentSpectrum):
                    solutions.append(tmp)
            elif compareSpectrums(s, parentSpectrum):
                out.append(tmp)
    return out

def sequencing(arr):
    arr = sorted(arr)
    uniq = uniqWeights()
    (parentSpectrum, parentMass) = arr2spectrum(arr)
    solutions = []
    peptides = [[]]
    while len(peptides) > 0:
        peptides = branchBound(peptides, uniq, parentMass, parentSpectrum, solutions)
    return solutions

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    arr = readArrayFromLine(fp)
    fp.close()
    out = sequencing(arr)
    for o in out:
        s = '-'.join(map(str, o))
        print s,
    print
