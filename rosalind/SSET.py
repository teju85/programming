import sys

if __name__ == '__main__':
    n = int(sys.argv[1])
    total = 1
    for i in range(0,n):
        total *= 2
        total %= 1000000
    print total
