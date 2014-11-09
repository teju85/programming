import sys

def func(s):
    words = s.split(' ')
    dic = {}
    for word in words:
        if not word in dic:
            dic[word] = 0
        dic[word] = dic[word] + 1
    for key in dic.keys():
        tmp = key + ' ' + str(dic[key])
        print tmp

if __name__ == '__main__':
    func(sys.argv[1])
