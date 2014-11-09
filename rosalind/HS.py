import sys
from common import readArrayFromLine

def maxHeapify(arr, i, length):
    left = (2 * i) + 1
    right = (2 * i) + 2
    largest = i
    if left < length and arr[left] > arr[largest]:
        largest = left
    if right < length and arr[right] > arr[largest]:
        largest = right
    if largest != i:
        t = arr[largest]
        arr[largest] = arr[i]
        arr[i] = t
        maxHeapify(arr, largest, length)

def heapBuild(arr):
    length = len(arr)
    for i in range(length/2,-1,-1):
        maxHeapify(arr, i, length)

def heapSort(arr):
    heapBuild(arr)
    for i in range(len(arr)-1,-1,-1):
        t = arr[0]
        arr[0] = arr[i]
        arr[i] = t
        maxHeapify(arr, 0, i)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    n = int(fp.readline())
    arr = readArrayFromLine(fp)
    fp.close()
    heapSort(arr)
    for a in arr:
        print a,
    print
