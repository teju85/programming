import sys
from common import readArrayFromLine

def getArray(inFile):
    f = open(inFile, 'r')
    f.readline()  # ignore first
    arr = readArrayFromLine(f)
    f.close()
    return arr

# TODO:
# another optimization is to use binary-search to
# fit this insertion and count for that as well
def numSwaps(arr):
    num = 0
    for i in range(1,len(arr)):
        k = i
        while k > 0 and arr[k] < arr[k-1]:
            num = num + 1
            t = arr[k]
            arr[k] = arr[k-1]
            arr[k-1] = t
            k = k - 1
    return num

if __name__ == '__main__':
    arr = getArray(sys.argv[1])
    print numSwaps(arr)
