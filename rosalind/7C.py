import sys
from common import stripLine

def longestRepeatInK(dna, k):
    n = len(dna)
    reps = {}
    for i in range(0,n-k+1):
        sub = dna[i:i+k]
        if sub not in reps:
            reps[sub] = 1
        else:
            return sub
    return ''

def binSearch(dna, start, end):
    if start > end:
        return ''
    # heuristic!!
    limit = 100
    if (end - start) <= limit:
        for i in range(end,start-1,-1):
            ll = longestRepeatInK(dna, i)
            if ll != '':
                return ll
        return ll
    mid = start + ((end - start) / 2)
    repeat = longestRepeatInK(dna, mid)
    if repeat == '':
        return binSearch(dna, start, mid-1)
    else:
        return binSearch(dna, mid+1, end)

def longestRepeat(dna):
    return binSearch(dna, 0, len(dna))

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    dna = stripLine(fp.readline())
    fp.close()
    print longestRepeat(dna)
