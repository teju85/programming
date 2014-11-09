import sys
from common import readArrayFromLine

def heap(arr):
    numSwaps = 0
    for i in range(len(arr)-1,0,-1):
        iby2 = (i - 1) / 2
        if arr[i] > arr[iby2]:
            t = arr[iby2]
            arr[iby2] = arr[i]
            arr[i] = t
            numSwaps += 1
    end = (len(arr) - 2) / 2
    for i in range(1,end+1):
        im2 = (2 * i) + 1
        if arr[i] < arr[im2]:
            t = arr[im2]
            arr[im2] = arr[i]
            arr[i] = t
            numSwaps += 1
        im2 = (2 * i) + 2
        if arr[i] < arr[im2]:
            t = arr[im2]
            arr[im2] = arr[i]
            arr[i] = t
            numSwaps += 1
    return (arr, numSwaps)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    n = int(fp.readline())
    arr = readArrayFromLine(fp)
    fp.close()
    num = 1
    while num > 0:
        (arr, num) = heap(arr)
    for a in arr:
        print a,
    print
