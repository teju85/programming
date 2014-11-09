import sys

def LtClumps(gene, l, k, t):
    kmers = {}
    for g in range(0,l-k):
        sub = gene[g:g+k]
        if sub not in kmers:
            kmers[sub] = 0
        kmers[sub] += 1
    for k in kmers.keys():
        if kmers[k] < t:
            del kmers[k]
    return kmers.keys()

def allClumps(gene, L, k, t):
    out = []
    l = len(gene)
    for g in range(0,l-L):
        sub = gene[g:g+L]
        out += LtClumps(sub, L, k, t)
        out = list(set(out))
    return out

if __name__ == '__main__':
    gene = sys.argv[1]
    k = int(sys.argv[2])
    L = int(sys.argv[3])
    t = int(sys.argv[4])
    kmers = allClumps(gene, L, k, t)
    for k in kmers:
        print k,
    print
