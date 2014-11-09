import string
import urllib2
from Bio import SwissProt
import sys


def getRecordFor(protId):
    handle = urllib2.urlopen('http://www.uniprot.org/uniprot/%s.txt' % protId)
    return SwissProt.read(handle)

def getBioProcessesFor(protId):
    record = getRecordFor(protId)
    cross = record.cross_references
    procs = []
    for c in cross:
        if c[0] != 'GO':
            continue
        if string.find(c[2], 'P:') != 0:
            continue
        procs.append(c[2][2:])
    return procs

if __name__ == '__main__':
    procs = getBioProcessesFor(sys.argv[1])
    for p in procs:
        print p
