import sys

def slow_func(n):
    if n == 0:
        return 0
    if n == 1:
        return 1
    return (slow_func(n-1) + slow_func(n-2))

def fast_func(n):
    arr = [0, 1]
    for i in range(2, n+1):
        arr.append(arr[i-1] + arr[i-2])
    return arr[n]

if __name__ == '__main__':
    #print slow_func(int(sys.argv[1]))
    print fast_func(int(sys.argv[1]))
