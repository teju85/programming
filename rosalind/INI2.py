import sys

def square(a, b):
    return ((a*a) + (b*b))

if __name__ == '__main__':
    print square(int(sys.argv[1]), int(sys.argv[2]))
