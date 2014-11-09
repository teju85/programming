import sys


if __name__ == '__main__':
    k = int(sys.argv[1])
    m = int(sys.argv[2])
    n = int(sys.argv[3])
    kmn = k + m + n
    kk = k * (k - 1) / 2.0
    km = k * m
    kn = k * n
    mm = m * (m - 1) * 3.0 / 4.0 / 2.0
    mn = m * n / 2.0
    dom = kk + km + kn + mm + mn
    total = kmn * (kmn - 1) / 2.0
    print dom/total
