import sys

def slice(s, a, b, c, d):
    out = s[a:b+1] + ' ' + s[c:d+1]
    return out

if __name__ == '__main__':
    s = sys.argv[1]
    a = int(sys.argv[2])
    b = int(sys.argv[3])
    c = int(sys.argv[4])
    d = int(sys.argv[5])
    print slice(s, a, b, c, d)
