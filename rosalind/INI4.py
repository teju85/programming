import sys

def func(a, b):
    sum = 0
    for num in range(a,b+1):
        if num % 2 == 1:
            sum += num
    return sum


if __name__ == '__main__':
    a = int(sys.argv[1])
    b = int(sys.argv[2])
    print func(a, b)
