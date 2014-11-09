import sys

def mostFreq(dnaString, k):
    freq = {}
    maxCount = 0
    maxKmers = []
    for idx in range(0,len(dnaString)-k+1):
        sub = dnaString[idx:idx+k]
        if sub in freq:
            continue
        freq[sub] = dnaString.count(sub)
        if maxCount < freq[sub]:
            maxCount = freq[sub]
    for sub in freq.keys():
        if freq[sub] == maxCount:
            maxKmers.append(sub)
    return maxKmers

if __name__ == '__main__':
    maxKmers = mostFreq(sys.argv[1], int(sys.argv[2]))
    for kmer in maxKmers:
        print kmer
