import sys
import string
from common import readFasta

def getGCpercent(dna, label):
    if dna == ''  or  label == '':
        return -1
    gc = string.count(dna, 'C') + string.count(dna, 'G')
    return (gc * 100.0) / len(dna)

def getMaxGC(dnas):
    gc = 0.0
    maxLabel = ''
    for d in dnas:
        (label, dna) = d
        percent = getGCpercent(dna, label)
        if percent > gc:
            maxLabel = label
            gc = percent
    return (maxLabel, gc)

if __name__ == '__main__':
    dnas = readFasta(sys.argv[1])
    (label, gc) = getMaxGC(dnas)
    print label
    print gc
