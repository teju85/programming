import sys
from Bio.Seq import Seq

def func(seq):
    bs = Seq(seq)
    dna = ['A', 'C', 'G', 'T']
    for d in dna:
        c = str(bs.count(d)) + ' '
        print c,
    print

if __name__ == '__main__':
    func(sys.argv[1])
