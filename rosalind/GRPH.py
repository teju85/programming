import sys
import string
from common import readFasta

def printAdjInt(inputs):
    k = 3
    size = len(inputs)
    for n1 in range(0,size):
        refDna = inputs[n1][1]
        if len(refDna) < k:
            continue
        for n2 in range(0,size):
            dna = inputs[n2][1]
            if refDna == dna:
                continue
            if len(dna) < k:
                continue
            if refDna[-k:] == dna[0:k]:
                print "%s %s" % (inputs[n1][0], inputs[n2][0])

def printAdj(inFile):
    inputs = readFasta(inFile)
    printAdjInt(inputs)

if __name__ == '__main__':
    printAdj(sys.argv[1])
