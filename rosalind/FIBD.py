import sys
import collections

def mortalRabbits(n, m):
    if n <= 0:
        return 0
    births = []
    deaths = []
    for i in range(0,m):
        births.append(0)
        deaths.append(0)
    births[0] += 1
    fn = 0
    for idx in range(1,n+1):
        nb = births.pop(0)
        nd = deaths.pop(0)
        births.append(0)
        deaths.append(0)
        for i in range(1,m):
            births[i] += nb
        deaths[m-1] += nb
        fn += (nb - nd)
    return fn

if __name__ == '__main__':
    n = int(sys.argv[1])
    m = int(sys.argv[2])
    print mortalRabbits(n, m)
