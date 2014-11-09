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

def score(pepSpec, spec):
    out = 0
    for sk in pepSpec.keys():
        if sk not in spec:
            continue
        out += min(pepSpec[sk], spec[sk])
    return out

def cut(arr, N):
    arr = sorted(arr, reverse=True)
    if len(arr) < N:
        return arr
    i = N
    while i < len(arr):
        if arr[i-1] != arr[i]:
            break
        i += 1
    return arr[:i]

def leaderBoardSequencing(arr, N):
    arr = sorted(arr)
    uniq = uniqWeights()
    (parentSpectrum, parentMass) = arr2spectrum(arr)
    peptides = [(1, [])]
    solutions = []
    while len(peptides) > 0:
        out = []
        for i in range(0,len(peptides)):
            for u in uniq:
                tmp = peptides[i][1] + [u]
                (s, mass) = generateSpectrum(tmp)
                sc = score(s, parentSpectrum)
                if mass > parentMass:
                    continue
                if mass == parentMass:
                    solutions.append((sc, tmp))
                out.append((sc, tmp))
        peptides = cut(out, N)
    return solutions

def findLeaderCyclo(solutions, arr):
    (parentSpectrum, parentMass) = arr2spectrum(arr)
    maxScore = -1
    leader = []
    for soln in solutions:
        s = generateCycloSpectrum(soln[1])
        sco = score(s, parentSpectrum)
        if sco > maxScore:
            leader = soln[1]
            maxScore = sco
    return (leader, maxScore)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    N = int(fp.readline())
    arr = readArrayFromLine(fp)
    fp.close()
    peps = leaderBoardSequencing(arr, N)
    (leader, tmp) = findLeaderCyclo(peps, arr)
    print '-'.join(map(str,leader))
