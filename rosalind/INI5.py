import sys

def func(inFile, outFile):
    inF = open(inFile, 'r')
    outF = open(outFile, 'w')
    idx = 1
    for line in inF:
        if idx % 2 == 0:
            outF.write(line)
        idx = idx + 1
    inF.close()
    outF.close()

if __name__ == '__main__':
    i = sys.argv[1]
    o = sys.argv[2]
    func(i, o)
