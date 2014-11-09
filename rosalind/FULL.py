import sys

mass = {
    'A' : 71.03711,
    'C' : 103.00919,
    'D' : 115.02694,
    'E' : 129.04259,
    'F' : 147.06841,
    'G' : 57.02146,
    'H' : 137.05891,
    'I' : 113.08406,
    'K' : 128.09496,
    'L' : 113.08406,
    'M' : 131.04049,
    'N' : 114.04293,
    'P' : 97.05276,
    'Q' : 128.05858,
    'R' : 156.10111,
    'S' : 87.03203,
    'T' : 101.04768,
    'V' : 99.06841,
    'W' : 186.07931,
    'Y' : 163.06333,
}

def findProtein(wt):
    for p in mass.keys():
        delta = abs(wt - mass[p]) / mass[p]
        if delta < 0.00005:
            return p
    return ''

def getDiffs(arr):
    pref = []
    for i in range(0,len(arr)):
        diff = []
        for j in range(i+1,len(arr)):
            p = findProtein(arr[j]-arr[i])
            if p != '':
                diff.append((j,p))
        pref.append(diff)
    return pref

def dfs(node, adjList, visited, prefix, N):
    visited.add(node)
    for adj in adjList[node]:
        (a, prot) = adj
        if a not in visited:
            prefix += prot
            if len(prefix) == N:
                return prefix
            prefix = dfs(a, adjList, visited, prefix, N)
            if len(prefix) == N:
                return prefix
    visited.remove(node)
    return prefix

def getProt(adjList, N):
    for i in range(0,len(adjList)):
        visited = set()
        prefix = dfs(i, adjList, visited, '', N)
        if prefix != '':
            return prefix
    return ''

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    total = float(fp.readline())
    arr = []
    for line in fp.readlines():
        arr.append(float(line))
    fp.close()
    N = (len(arr) - 2) / 2
    arr = sorted(arr)
    pref = getDiffs(arr)
    print getProt(pref, N)
