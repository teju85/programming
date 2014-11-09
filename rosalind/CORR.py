import sys
from common import readFasta, revComp, hamming

def addElement(dMap, elem):
    if elem in dMap:
        dMap[elem][0] += 1
        return
    rev = revComp(elem)
    if rev in dMap:
        dMap[rev][1] += 1
        return
    dMap[elem] = [1, 0]

def isFound(dMap, elem):
    if elem in dMap  and  dMap[elem][0]+dMap[elem][1] == 2:
        return True
    rev = revComp(elem)
    if rev in dMap  and  dMap[rev][0]+dMap[rev][1] == 2:
        return True
    return False

def separateSequences(dMap):
    right = []
    wrong = []
    for key in dMap.keys():
        total = dMap[key][0] + dMap[key][1]
        if total < 2:
            wrong.append(key)
        else:
            right.append(key)
    return (right, wrong)

def findOneError(keys, k):
    rev = revComp(k)
    for t in keys:
        if hamming(t, k) == 1:
            return t
        if hamming(t, rev) == 1:
            return revComp(t)
    return ''

def findCorrections(right, wrong):
    out = []
    for key in wrong:
        rev = revComp(key)
        for r in right:
            if hamming(r, key) == 1:
                out.append((key, r))
            elif hamming(r, rev) == 1:
                out.append((key, revComp(r)))
    return out

if __name__ == '__main__':
    dnas = readFasta(sys.argv[1])
    dMap = {}
    for d in dnas:
        addElement(dMap, d[1])
    (right, wrong) = separateSequences(dMap)
    out = findCorrections(right, wrong)
    for o in out:
        print "%s->%s" % o
