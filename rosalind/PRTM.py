import sys

def massTable():
    wts = {}
    wts['A'] = 71.03711
    wts['C'] = 103.00919
    wts['D'] = 115.02694
    wts['E'] = 129.04259
    wts['F'] = 147.06841
    wts['G'] = 57.02146
    wts['H'] = 137.05891
    wts['I'] = 113.08406
    wts['K'] = 128.09496
    wts['L'] = 113.08406
    wts['M'] = 131.04049
    wts['N'] = 114.04293
    wts['P'] = 97.05276
    wts['Q'] = 128.05858
    wts['R'] = 156.10111
    wts['S'] = 87.03203
    wts['T'] = 101.04768
    wts['V'] = 99.06841
    wts['W'] = 186.07931
    wts['Y'] = 163.06333
    return wts

def weight(prot):
    water = 18.01056
    table = massTable()
    wt = 0.0
    size = len(prot)
    for i in range(0,size):
        wt += table[prot[i]]
    return wt

if __name__ == '__main__':
    print weight(sys.argv[1])
