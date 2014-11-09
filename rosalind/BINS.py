import sys
from common import readArrayFromLine

def binSearch(arr, val, start, end):
    if start > end:
        return -1
    num = end - start
    mid = start + (num / 2)
    if arr[mid] == val:
        return mid + 1
    if num <= 1:
        return -1
    if arr[mid] < val:
        return binSearch(arr, val, mid+1, end)
    if arr[mid] > val:
        return binSearch(arr, val, start, mid)

def func(arr, k):
    for number in k:
        pos = binSearch(arr, number, 0, len(arr))
        s = str(pos)
        print s,
    print

def readParams(inFile):
    f = open(inFile, 'r')
    f.readline() # n
    f.readline() # m
    arr = readArrayFromLine(f)
    k = readArrayFromLine(f)
    f.close()
    return (arr, k)

if __name__ == '__main__':
    (arr, k) = readParams(sys.argv[1])
    func(arr, k)
