import sys
from common import readFasta

comp = {}
comp['A'] = 'U'
comp['U'] = 'A'
comp['C'] = 'G'
comp['G'] = 'C'

motMap = {}

def motzkin(dna):
    if len(dna) <= 1:
        return 1
    if dna in motMap:
        return motMap[dna]
    num = motzkin(dna[1:]) % 1000000
    for k in range(1,len(dna)):
        if dna[0] == comp[dna[k]]:
            num += motzkin(dna[1:k]) * motzkin(dna[k+1:])
            num %= 1000000
    motMap[dna] = num
    #print num, dna
    return num

if __name__ == '__main__':
    dna = readFasta(sys.argv[1])[0][1]
    print motzkin(dna)
