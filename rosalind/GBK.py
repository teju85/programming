from Bio import Entrez
import sys

def readGenBank(organism, fromDate, toDate):
    pubDate = 'Publication Date'
    query = '(%s[Organism]) AND (("%s"[%s] : "%s"[%s]))' % \
            (organism, fromDate, pubDate, toDate, pubDate)
    Entrez.email = 'rao.thejaswi@gmail.com'
    handle = Entrez.esearch(db='nucleotide',term=query)
    record = Entrez.read(handle)
    return record['Count']

if __name__ == '__main__':
    print readGenBank(sys.argv[1], sys.argv[2], sys.argv[3])
