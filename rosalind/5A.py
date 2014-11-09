import sys
from common import stripLine

minChangeMap = {}

def initMinChangeMap(coins):
    for c in coins:
        minChangeMap[c] = 1

def quotientReminder(change, coins):
    ret = []
    for c in coins:
        q = change / c
        r = change % c
        if q <= 0:
            continue
        ret.append((q, r, c))
    return ret

def recurseChange(change, coins):
    if change in minChangeMap:
        return minChangeMap[change]
    qr = quotientReminder(change, coins)
    minCount = -1
    for elem in qr:
        count = elem[0]
        if minCount != -1  and  count > minCount:
            break
        if elem[1] > 0:
            count += recurseChange(elem[1], coins)
        if minCount == -1  or  count < minCount:
            minCount = count
    minChangeMap[change] = minCount
    return minCount

def changeProblem(change, coins):
    coins = sorted(coins, reverse=True)
    initMinChangeMap(coins)
    return recurseChange(change, coins)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    change = int(fp.readline())
    line = stripLine(fp.readline())
    fp.close()
    coins = []
    for s in line.split(','):
        coins.append(int(s))
    print changeProblem(change, coins)
