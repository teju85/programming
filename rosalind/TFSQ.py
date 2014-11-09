import sys
from Bio import SeqIO

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    outFp = open('aa.txt', 'w')
    count = SeqIO.convert(fp, 'fastq', outFp, 'fasta')
    print count
    fp.close()
    outFp.close()
