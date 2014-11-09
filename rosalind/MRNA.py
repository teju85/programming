import sys
from common import getRnaCodonTable

def reverseMap():
    table = getRnaCodonTable()
    rev = {}
    for k in table.keys():
        v = table[k]
        if v not in rev:
            rev[v] = []
        rev[v].append(k)
    return rev

def numRnas(prot):
    rev = reverseMap()
    num = 1
    size = len(prot)
    for i in range(0,size):
        num *= len(rev[prot[i]])
        num %= 1000000
    return ((num * 3) % 1000000)

if __name__ == '__main__':
    protein = sys.argv[1]
    print numRnas(protein)
