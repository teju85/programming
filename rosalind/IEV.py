import sys

def expDominant(n1, n2, n3, n4, n5, n6):
    p1 = 1.0
    p2 = 1.0
    p3 = 1.0
    p4 = 0.75
    p5 = 0.5
    p6 = 0.0
    exp = (n1 * p1) + (n2 * p2) + (n3 * p3)
    exp += ((n4 * p4) + (n5 * p5) + (n6 * p6))
    exp *= 2.0
    return exp

if __name__ == '__main__':
    n1 = int(sys.argv[1])
    n2 = int(sys.argv[2])
    n3 = int(sys.argv[3])
    n4 = int(sys.argv[4])
    n5 = int(sys.argv[5])
    n6 = int(sys.argv[6])
    print expDominant(n1, n2, n3, n4, n5, n6)
