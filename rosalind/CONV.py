import sys
from common import readFloatArrayFromLine

def inTheMapApprox(m, key):
    for k in m.keys():
        if abs(k - key) <= 0.00001:
            return k
    return None

def minkoDiff(s1, s2):
    out = {}
    for a in s1:
        for b in s2:
            delta = a - b
            key = inTheMapApprox(out, delta)
            if key is None:
                key = delta
                out[key] = 0
            out[key] += 1
    return out

def maxMultiplicity(m):
    maxi = -1
    maxVal = 0
    for k in m.keys():
        if m[k] > maxi:
            maxi = m[k]
            maxVal = k
    return (maxi, maxVal)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    S1 = readFloatArrayFromLine(fp)
    S2 = readFloatArrayFromLine(fp)
    fp.close()
    m = minkoDiff(S1, S2)
    (maxi, val) = maxMultiplicity(m)
    print maxi, val
