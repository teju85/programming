import sys
from common import readFasta
from sss import shortestSuperString

if __name__ == '__main__':
    dnas = readFasta(sys.argv[1])
    print shortestSuperString(dnas)
