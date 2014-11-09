import sys
from multiprocessing import Process, Queue
from common import readLine

def isApproxMatch(a, b, d):
    mis = 0
    status = True
    for i in range(0,len(a)):
        if a[i] != b[i]:
            mis += 1
        if mis > d:
            status = False
            break
    return status

def countApproxMatch(dna, sub, d):
    ls = len(sub)
    ld = len(dna)
    count = 0
    for i in range(0,ld-ls+1):
        ss = dna[i:i+ls]
        if isApproxMatch(ss, sub, d):
            count += 1
    return count

def generateMismatches(s, d):
    uniq = set()
    if d <= 0:
        uniq.add(s)
        return uniq
    for i in range(0,len(s)):
        for g in 'ACGT':
            t = s[:i] + g + s[i+1:]
            tmp = generateMismatches(t, d-1)
            uniq.update(tmp)
    return uniq

def generateKeys(dnaString, k, d):
    subs = set()
    for idx in range(0,len(dnaString)-k+1):
        subDna = dnaString[idx:idx+k]
        subs.update(generateMismatches(subDna, d))
    return subs

def run(que, dnaString, d, keys, tid, numWork):
    freq = {}
    cnt = 0
    start = numWork * tid
    end = numWork * (tid + 1)
    if end > len(keys):
        end = len(keys)
    print "Process %d: %d -> %d" % (tid, start, end)
    for i in range(start,end):
        k = keys[i]
        cnt += 1
        freq[k] = countApproxMatch(dnaString, k, d)
        if cnt % 5000 == 0:
            print "Process %d: %d" % (tid, cnt)
    print "tid=%d %d" % ((tid), len(freq))
    que.put(freq)

def mostFreq(dnaString, k, d):
    subs = list(generateKeys(dnaString, k, d))
    numSubs = len(subs)
    numThreads = 8
    numWork = (numSubs + numThreads - 1) / numThreads
    print "numKeys=%d numWork=%d" % (numSubs, numWork)
    threads = []
    queues = []
    freq = [ {}  for tid in range(0, numThreads)]
    for tid in range(0, numThreads):
        q = Queue()
        p = Process(target=run, args=(q, dnaString, d, subs, tid, numWork))
        threads.append(p)
        queues.append(q)
    for t in threads:
        t.start()
    for tid in range(0, numThreads):
        freq[tid] = queues[tid].get()
    maxCount = 0
    maxKmers = []
    finalFreq = {}
    for tid in range(0, numThreads):
        print "numKeys in id=%d %d" % (tid, len(freq[tid]))
        for k in freq[tid].keys():
            if k not in finalFreq:
                finalFreq[k] = 0
            finalFreq[k] += freq[tid][k]
    for sub in finalFreq.keys():
        if maxCount < finalFreq[sub]:
            maxCount = finalFreq[sub]
    for sub in finalFreq.keys():
        if maxCount == finalFreq[sub]:
            maxKmers.append(sub)
    return maxKmers

if __name__ == '__main__':
    fp = open(sys.argv[1])
    Text = readLine(fp)
    line = readLine(fp)
    line = line.split(' ')
    ilist = [int(i) for i in line]
    fp.close()
    maxKmers = mostFreq(Text, ilist[0], ilist[1])
    for kmer in maxKmers:
        print kmer,
    print
