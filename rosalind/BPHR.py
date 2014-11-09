import sys
from Bio import SeqIO

def average(arr, col):
    avg = 0.0
    for i in range(0,len(arr)):
        avg += arr[i][col]
    avg /= len(arr)
    return avg

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    thresh = int(fp.readline())
    qual = []
    for record in SeqIO.parse(fp, 'fastq'):
        qual.append(record.letter_annotations['phred_quality'])
    fp.close()
    num = 0
    for i in range(0,len(qual[0])):
        if average(qual, i) < thresh:
            num += 1
    print num
