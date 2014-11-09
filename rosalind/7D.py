import sys
from common import stripLine

def newNode(graph, root, char, currNode, pos):
    currNode += 1
    graph['adj'][root][char] = [currNode, pos, len(text), False]
    graph['adj'][currNode] = {}
    return currNode

def splitNode(graph, root, char, currNode, text):
    rootData = graph['adj'][root][char]
    if not rootData[3]:
        rootData[3] = True
        rootData[2] = rootData[1] + 1
        c = text[rootData[1]+1]
        currNode = newNode(graph, rootData[0], c, currNode, rootData[1]+1)
    root = rootData[0]
    return (currNode, root)

def generateSuffixTree(text):
    graph = {}
    graph['adj'] = {}
    root = 1
    graph['adj'][root] = {}
    currNode = root
    for i in range(0,len(text)):
        root = 1
        for j in range(i,len(text)):
            char = text[j]
            if char not in graph['adj'][root]:
                currNode = newNode(graph, root, char, currNode, j)
                break
            (currNode, root) = splitNode(graph, root, char, currNode, text)
    graph['root'] = 1
    graph['maxNode'] = currNode
    return graph

def printEdges(graph, text):
    for i in range(graph['root'],graph['maxNode']+1):
        node = graph['adj'][i]
        for k in node.keys():
            data = node[k]
            print text[data[1]:data[2]]

if __name__ == '__main__':
    fp = open(sys.argv[1], 'r')
    text = stripLine(fp.readline())
    fp.close()
    graph = generateSuffixTree(text)
    printEdges(graph, text)
