from Bio import Entrez
from Bio import SeqIO
import sys
from common import readFastaFromFp

def minLenId(dnas):
    minLen = 0
    minId = -1
    for i in range(0,len(dnas)):
        length = len(dnas[i][1])
        if minId == -1:
            minLen = length
            minId = i
        elif length < minLen:
            minLen = length
            minId = i
    return minId

def fetchFasta(ids):
    Entrez.email = 'rao.thejaswi@gmail.com'
    handle = Entrez.efetch(db='nucleotide', id=ids[1:], rettype='fasta')
    dnas = readFastaFromFp(handle)
    minId = minLenId(dnas)
    handle = Entrez.efetch(db='nucleotide', id=ids[minId+1], rettype='fasta')
    records = handle.read()
    print records

if __name__ == '__main__':
    fetchFasta(sys.argv)
