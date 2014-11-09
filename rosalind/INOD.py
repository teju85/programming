import sys

def count(n, fromBelow):
    if n <= 2:
        return fromBelow
    if n == 3:
        return 1 + fromBelow
    remaining = n % 2
    n /= 2
    num = n + count(n, remaining) + fromBelow
    return num

if __name__ == '__main__':
    print count(int(sys.argv[1]), 0)
