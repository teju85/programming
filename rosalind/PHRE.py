import sys
from Bio import SeqIO

def average(arr):
    avg = 0.0
    for a in arr:
        avg += a
    avg /= len(arr)
    return avg

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    thresh = int(fp.readline())
    num = 0
    for record in SeqIO.parse(fp, 'fastq'):
        av = average(record.letter_annotations['phred_quality'])
        if av < thresh:
            num += 1
    fp.close()
    print num
