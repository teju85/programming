import sys
from Bio import SeqIO
from common import readIntPair

def percentAboveQuality(arr, thresh):
    num = 0
    for a in arr:
        if a >= thresh:
            num += 1
    above = (num * 100.0) / len(arr)
    return above

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    (thresh, percent) = readIntPair(fp)
    num = 0
    for record in SeqIO.parse(fp, 'fastq'):
        above = percentAboveQuality(record.letter_annotations['phred_quality'], thresh)
        if above >= percent:
            num += 1
    fp.close()
    print num
