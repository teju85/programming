import sys
from common import readArrayFromLine

def minHeapify(arr, i, length):
    left = (2 * i) + 1
    right = (2 * i) + 2
    smallest = i
    if left < length and arr[left] < arr[smallest]:
        smallest = left
    if right < length and arr[right] < arr[smallest]:
        smallest = right
    if smallest != i:
        t = arr[smallest]
        arr[smallest] = arr[i]
        arr[i] = t
        minHeapify(arr, smallest, length)

def heapBuild(arr):
    length = len(arr)
    for i in range(length/2,-1,-1):
        minHeapify(arr, i, length)

def heapPartialSort(arr, k):
    heapBuild(arr)
    for i in range(len(arr)-1,len(arr)-k-1,-1):
        t = arr[0]
        arr[0] = arr[i]
        arr[i] = t
        minHeapify(arr, 0, i)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    n = int(fp.readline())
    arr = readArrayFromLine(fp)
    k = int(fp.readline())
    fp.close()
    heapPartialSort(arr, k)
    for i in range(len(arr)-1,len(arr)-k-1,-1):
        print arr[i],
    print
