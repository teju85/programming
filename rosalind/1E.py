import sys

def minSkew(gene):
    l = len(gene)
    skewAcc = 0
    minVal = l
    skewPos = []
    for i in range(0,l):
        if gene[i] == 'C':
            skewAcc -= 1
        elif gene[i] == 'G':
            skewAcc += 1
        if skewAcc < minVal:
            minVal = skewAcc
            skewPos = [i+1]
        elif skewAcc == minVal:
            skewPos.append(i+1)
    return skewPos

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    gene = fp.readline()
    fp.close()
    skews = minSkew(gene)
    for s in skews:
        print s,
    print
