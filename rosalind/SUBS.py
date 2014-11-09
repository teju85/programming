import sys

def positions(s, t):
    size = len(s)
    pos = 0
    while True:
        pos = s.find(t, pos)
        if pos < 0:
            break
        pos += 1  # 1-based numbering
        print pos,
    print

if __name__ == '__main__':
    positions(sys.argv[1], sys.argv[2])
