import sys


if __name__ == '__main__':
    s = sys.argv[1]
    for nt in ['A', 'C', 'G', 'T']:
        print s.count(nt),
    print
