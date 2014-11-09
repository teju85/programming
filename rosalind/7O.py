import sys
from multiprocessing import Process, Queue
from common import readLine

def approxMatches(patt, text, d):
    out = []
    lp = len(patt)
    lt = len(text) - lp
    for i in range(0,lt+1):
        num = 0
        for j in range(0,lp):
            if text[i+j] != patt[j]:
                num += 1
            if num > d:
                break
        if num <= d:
            out.append(i)
    return out

def run(que, text, patts, d, tid, numWork):
    out = []
    cnt = 0
    start = numWork * tid
    end = numWork * (tid + 1)
    if end > len(patts):
        end = len(patts)
    print "Process %d: %d -> %d" % (tid, start, end)
    for i in range(start,end):
        k = patts[i]
        cnt += 1
        out += approxMatches(k, text, d)
        if cnt % 100 == 0:
            print "Process %d: %d" % (tid, cnt)
    print "tid=%d %d" % ((tid), len(out))
    que.put(out)

def findAll(patts, text, d):
    numPatts = len(patts)
    numThreads = 8
    numWork = (numPatts + numThreads - 1) / numThreads
    print "numPatts=%d numWork=%d" % (numPatts, numWork)
    threads = []
    queues = []
    for tid in range(0,numThreads):
        q = Queue()
        p = Process(target=run, args=(q, text, patts, d, tid, numWork))
        threads.append(p)
        queues.append(q)
    for t in threads:
        t.start()
    out = []
    for tid in range(0,numThreads):
        out += queues[tid].get()
    out = sorted(out)
    for p in out:
        print p,
    print

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    text = readLine(fp)
    line = readLine(fp)
    patts = line.split(' ')
    d = int(fp.readline())
    fp.close()
    print len(patts)
    findAll(patts, text, d)
