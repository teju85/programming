import sys

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

def findProtein(wt):
    for p in mass.keys():
        delta = abs(wt - mass[p]) / mass[p]
        if delta < 0.00005:
            return p
    return ''

def getProteinString(weights):
    prot = ''
    for i in range(1,len(weights)):
        delta = weights[i] - weights[i-1]
        prot += findProtein(delta)
    return prot

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    weights = []
    for line in fp.readlines():
        weights.append(float(line))
    fp.close()
    print getProteinString(weights)
