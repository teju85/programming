import sys
from common import readFloatArrayFromLine, stripLine

def inTheMapApprox(m, key):
    for k in m.keys():
        if abs(k - key) <= 0.00001:
            return k
    return None

def minkoDiff(s1, s2):
    out = {}
    for a in s1:
        for b in s2:
            delta = a - b
            key = inTheMapApprox(out, delta)
            if key is None:
                key = delta
                out[key] = 0
            out[key] += 1
    return out

def maxMultiplicity(m):
    maxi = -1
    maxVal = 0
    for k in m.keys():
        if m[k] > maxi:
            maxi = m[k]
            maxVal = k
    return (maxi, maxVal)

mass = {
    'A' : 71.03711,
    'C' : 103.00919,
    'D' : 115.02694,
    'E' : 129.04259,
    'F' : 147.06841,
    'G' : 57.02146,
    'H' : 137.05891,
    'I' : 113.08406,
    'K' : 128.09496,
    'L' : 113.08406,
    'M' : 131.04049,
    'N' : 114.04293,
    'P' : 97.05276,
    'Q' : 128.05858,
    'R' : 156.10111,
    'S' : 87.03203,
    'T' : 101.04768,
    'V' : 99.06841,
    'W' : 186.07931,
    'Y' : 163.06333,
}

def completeSpectrum(prot):
    out = []
    add = 0.0
    for i in range(0,len(prot)):
        add += mass[prot[i]]
        out.append(add)
#    for i in range(len(prot)-1,0,-1):
#        add -= mass[prot[i]]
#        out.append(add)
    out = sorted(out)
    return out

def maxDiff(R, prot):
    sk = completeSpectrum(prot)
    m = minkoDiff(R, sk)
    (maxi, val) = maxMultiplicity(m)
    return (maxi, val)

def protMatch(R, prots):
    R = sorted(R)
    maxMult = 0
    maxProt = ''
    for p in prots:
        (m, v) = maxDiff(R, p)
        if m > maxMult:
            maxProt = p
            maxMult = m
    return (maxMult, maxProt)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    N = int(fp.readline())
    prots = []
    for i in range(0,N):
        prots.append(stripLine(fp.readline()))
    R = []
    for line in fp.readlines():
        R.append(float(line))
    fp.close()
    (m, p) = protMatch(R, prots)
    print m
    print p
