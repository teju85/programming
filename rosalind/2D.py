import sys

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

def countPeptides(mass, table):
    mat = [[0 for j in range(0,len(table))] for i in range(0,mass+1)]
    for i in range(0,len(table)):
        mat[0][i] = 1
    for i in range(1,mass+1):
        for j in range(0,len(table)):
            remaining = i - table[j]
            if remaining >= 0:
                withJ = mat[remaining][j]
            else:
                withJ = 0
            withoutJ = 0
            for t in range(0,j):
                withoutJ += mat[i][t]
            if j >= 1:
                withoutJ = mat[i][j-1]
            else:
                withoutJ = 0
            mat[i][j] = withJ + withoutJ
    #print mat
    return mat[mass][-1]

if __name__ == '__main__':
    mass = int(sys.argv[1])
    table = []
    for k in massTable.keys():
        table.append(massTable[k])
    table = sorted(table)
    print countPeptides(mass, table)
