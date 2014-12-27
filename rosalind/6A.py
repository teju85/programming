import sys
from common import stripLine, printPermutation

def findNumber(perm, num):
    for i in range(0,len(perm)):
        ab = perm[i]
        if ab < 0:
            ab = -ab
        if ab == num:
            return i
    return None  # shouldn't occur!

def reversal(perm, start, end):
    while start <= end:
        tmp = perm[start]
        perm[start] = -perm[end]
        perm[end] = -tmp
        start += 1
        end -= 1

def greedySorting(perm):
    for i in range(0,len(perm)):
        pos = findNumber(perm, i+1)
        if pos != i:
            reversal(perm, i, pos)
            printPermutation(perm)
        if perm[i] < 0:
            reversal(perm, i, i)
            printPermutation(perm)

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    line = stripLine(fp.readline())
    fp.close()
    line = line[1:len(line)-1]
    nums = map(int, line.split(' '))
    greedySorting(nums)
