import string
import urllib2
import math

def stripLine(line):
    line = line.strip('\n')
    line = line.strip('\r')
    return line

def readFastaFromString(lines):
    label = ''
    dna = ''
    data = []
    for line in lines:
        line = stripLine(line)
        if len(line) <= 0:
            continue
        if line[0] == '>':
            if label != '' and dna != '':
                data.append((label, dna))
            label = line[1:]
            dna = ''
            continue
        dna += line
    if label != '' and dna != '':
        data.append((label, dna))
    return data

def readFastaFromFp(fp):
    return readFastaFromString(fp.readlines())

def readFasta(inFile):
    fp = open(inFile)
    data = readFastaFromFp(fp)
    fp.close()
    return data

def readFastaFromUniProt(protId):
    url = 'http://www.uniprot.org/uniprot/%s.fasta' % (protId)
    req = urllib2.Request(url)
    conn = urllib2.urlopen(req)
    return readFastaFromFp(conn)

def readArrayFromLine(fp):
    arr = []
    line = fp.readline()
    tmp = line.split(' ')
    for t in tmp:
        arr.append(int(t))
    return arr

def readFloatArrayFromLine(fp):
    arr = []
    line = fp.readline()
    tmp = line.split(' ')
    for t in tmp:
        arr.append(float(t))
    return arr

def readIntPair(fp):
    s = fp.readline()
    ss = s.split(' ')
    return (int(ss[0]), int(ss[1]))

def readIntTriplet(fp):
    s = fp.readline()
    ss = s.split(' ')
    return (int(ss[0]), int(ss[1]), int(ss[2]))

def generateAdjMatrix(graph, directed=False, weighted=False):
    graph['adj'] = []
    for i in range(graph['numV']):
        graph['adj'].append([])
    for e in graph['edges']:
        x = e[0] - 1
        y = e[1] - 1
        if weighted:
            graph['adj'][x].append((y, e[2]))
        else:
            graph['adj'][x].append(y)
        if not directed:
            if weighted:
                graph['adj'][y].append((x, e[2]))
            else:
                graph['adj'][y].append(x)
    graph['deg'] = []
    for v in range(graph['numV']):
        graph['deg'].append(len(graph['adj'][v]))

def readEdgeListFromFp(f, directed=False, weighted=False):
    graph = {}
    graph['numV'] = 0
    graph['numE'] = 0
    graph['edges'] = []
    (graph['numV'], graph['numE']) = readIntPair(f)
    for i in range(graph['numE']):
        if weighted:
            graph['edges'].append(readIntTriplet(f))
        else:
            graph['edges'].append(readIntPair(f))
    generateAdjMatrix(graph, directed, weighted)
    return graph

def readEdgeList(inFile, directed=False, weighted=False):
    f = open(inFile, 'r')
    graph = readEdgeListFromFp(f, directed, weighted)
    f.close()
    return graph

def readAdjList(inFile, directed=False):
    f = open(inFile, 'r')
    graph = {}
    graph['numV'] = 0
    graph['numE'] = 0
    graph['edges'] = []
    graph['numV'] = int(f.readline())
    for line in f.readlines():
        ss = line.split(' ')
        graph['edges'].append((int(ss[0]), int(ss[1])))
    f.close()
    graph['numE'] = len(graph['edges'])
    generateAdjMatrix(graph)
    return graph

def graphTranspose(graph, weighted=False):
    out = {}
    out['numV'] = graph['numV']
    out['numE'] = graph['numE']
    out['edges'] = []
    for adj in graph['edges']:
        if weighted:
            out['edges'].append((adj[1], adj[0], adj[2]))
        else:
            out['edges'].append((adj[1], adj[0]))
    generateAdjMatrix(out, True, weighted)
    return out

def readLine(fp):
    line = fp.readline()
    return stripLine(line)

def isStopCodon(s):
    stopCodons = ['TAA', 'TAG', 'TGA']
    return (s in stopCodons)

def isStartCodon(s):
    return (s == 'ATG')

def getDnaCodonTable():
    table = {}
    table['TTT'] = 'F'
    table['CTT'] = 'L'
    table['ATT'] = 'I'
    table['GTT'] = 'V'
    table['TTC'] = 'F'
    table['CTC'] = 'L'
    table['ATC'] = 'I'
    table['GTC'] = 'V'
    table['TTA'] = 'L'
    table['CTA'] = 'L'
    table['ATA'] = 'I'
    table['GTA'] = 'V'
    table['TTG'] = 'L'
    table['CTG'] = 'L'
    table['ATG'] = 'M'
    table['GTG'] = 'V'
    table['TCT'] = 'S'
    table['CCT'] = 'P'
    table['ACT'] = 'T'
    table['GCT'] = 'A'
    table['TCC'] = 'S'
    table['CCC'] = 'P'
    table['ACC'] = 'T'
    table['GCC'] = 'A'
    table['TCA'] = 'S'
    table['CCA'] = 'P'
    table['ACA'] = 'T'
    table['GCA'] = 'A'
    table['TCG'] = 'S'
    table['CCG'] = 'P'
    table['ACG'] = 'T'
    table['GCG'] = 'A'
    table['TAT'] = 'Y'
    table['CAT'] = 'H'
    table['AAT'] = 'N'
    table['GAT'] = 'D'
    table['TAC'] = 'Y'
    table['CAC'] = 'H'
    table['AAC'] = 'N'
    table['GAC'] = 'D'
    #table['TAA'] = 'Stop'
    table['CAA'] = 'Q'
    table['AAA'] = 'K'
    table['GAA'] = 'E'
    #table['TAG'] = 'Stop'
    table['CAG'] = 'Q'
    table['AAG'] = 'K'
    table['GAG'] = 'E'
    table['TGT'] = 'C'
    table['CGT'] = 'R'
    table['AGT'] = 'S'
    table['GGT'] = 'G'
    table['TGC'] = 'C'
    table['CGC'] = 'R'
    table['AGC'] = 'S'
    table['GGC'] = 'G'
    #table['TGA'] = 'Stop'
    table['CGA'] = 'R'
    table['AGA'] = 'R'
    table['GGA'] = 'G'
    table['TGG'] = 'W'
    table['CGG'] = 'R'
    table['AGG'] = 'R'
    table['GGG'] = 'G'
    return table

def dna2prot(dna, table):
    prot = ''
    for i in range(0,len(dna)-2,3):
        codon = dna[i:i+3]
        if isStopCodon(codon):
            return prot
            break
        prot += table[codon]
    return ''

comp = {}
comp['A'] = 'T'
comp['T'] = 'A'
comp['C'] = 'G'
comp['G'] = 'C'

def revComp(dnaString):
    rev = dnaString[::-1]
    out = ''
    for c in rev:
        out += comp[c]
    return out

def getRnaCodonTable():
    table = {}
    table['UUU'] = 'F'
    table['CUU'] = 'L'
    table['AUU'] = 'I'
    table['GUU'] = 'V'
    table['UUC'] = 'F'
    table['CUC'] = 'L'
    table['AUC'] = 'I'
    table['GUC'] = 'V'
    table['UUA'] = 'L'
    table['CUA'] = 'L'
    table['AUA'] = 'I'
    table['GUA'] = 'V'
    table['UUG'] = 'L'
    table['CUG'] = 'L'
    table['AUG'] = 'M'
    table['GUG'] = 'V'
    table['UCU'] = 'S'
    table['CCU'] = 'P'
    table['ACU'] = 'T'
    table['GCU'] = 'A'
    table['UCC'] = 'S'
    table['CCC'] = 'P'
    table['ACC'] = 'T'
    table['GCC'] = 'A'
    table['UCA'] = 'S'
    table['CCA'] = 'P'
    table['ACA'] = 'T'
    table['GCA'] = 'A'
    table['UCG'] = 'S'
    table['CCG'] = 'P'
    table['ACG'] = 'T'
    table['GCG'] = 'A'
    table['UAU'] = 'Y'
    table['CAU'] = 'H'
    table['AAU'] = 'N'
    table['GAU'] = 'D'
    table['UAC'] = 'Y'
    table['CAC'] = 'H'
    table['AAC'] = 'N'
    table['GAC'] = 'D'
    #table['UAA'] = 'Stop'
    table['CAA'] = 'Q'
    table['AAA'] = 'K'
    table['GAA'] = 'E'
    #table['UAG'] = 'Stop'
    table['CAG'] = 'Q'
    table['AAG'] = 'K'
    table['GAG'] = 'E'
    table['UGU'] = 'C'
    table['CGU'] = 'R'
    table['AGU'] = 'S'
    table['GGU'] = 'G'
    table['UGC'] = 'C'
    table['CGC'] = 'R'
    table['AGC'] = 'S'
    table['GGC'] = 'G'
    #table['UGA'] = 'Stop'
    table['CGA'] = 'R'
    table['AGA'] = 'R'
    table['GGA'] = 'G'
    table['UGG'] = 'W'
    table['CGG'] = 'R'
    table['AGG'] = 'R'
    table['GGG'] = 'G'
    return table

def rna2prot(rna, table):
    prot = ''
    for i in range(0,len(rna),3):
        codon = rna[i:i+3]
        if codon not in table:
            continue
        prot += table[codon]
    return prot


def _dfs(graph, node, color, visited):
    visited[node] = color
    for adj in graph['adj'][node]:
        if adj in visited:
            continue
        _dfs(graph, adj, color, visited)
def _findNextForest(visited, numV):
    for i in range(0,numV):
        if i not in visited:
            return i
    return -1
def connectedComponents(graph):
    color = 0
    visited = {}
    node = 0
    while node >= 0:
        _dfs(graph, node, color, visited)
        node = _findNextForest(visited, graph['numV'])
        color += 1
    return (visited, color)

def dfs(graph, node, visited):
    visited.add(node)
    for adj in graph['adj'][node]:
        if adj not in visited:
            dfs(graph, adj, visited)

def patt2num(patt, symMap):
    n = 0
    lp = len(patt)
    w = 1
    for i in range(lp-1,-1,-1):
        n += (symMap[patt[i]] * w)
        w *= len(symMap)
    return n

def num2patt(num, pattLen, symMap):
    size = len(symMap)
    p = ''
    for i in range(0,pattLen):
        p = symMap[num%size] + p
        num /= size
    return p

def hamming(s, t):
    length = len(s)
    diff = 0
    for i in range(0,length):
        if s[i] != t[i]:
            diff += 1
    return diff

def factorial(n):
    if n <= 1:
        return 1
    return n * factorial(n-1)

def lcsm(a, b):
    la = len(a) + 1
    lb = len(b) + 1
    mat = [[0 for x in range(0,lb)] for x in range(0,la)]
    subStrs = []
    maxLen = 0
    for i in range(1,la):
        ca = a[i-1]
        for j in range(1,lb):
            cb = b[j-1]
            if ca == cb:
                mat[i][j] = mat[i-1][j-1] + 1
                if mat[i][j] > maxLen:
                    maxLen = mat[i][j]
                    subStrs = []
                    subStrs.append(a[i-maxLen:i])
                elif mat[i][j] == maxLen:
                    subStrs.append(a[i-maxLen:i])
            else:
                mat[i][j] = 0
    return subStrs

def _dfsTopological(graph, node, visited, stack):
    visited.add(node)
    for adj in graph['adj'][node]:
        if adj not in visited:
            _dfsTopological(graph, adj, visited, stack)
    stack.append(node)

def topologicalSort(graph):
    stack = []
    visited = set()
    for i in range(0,graph['numV']):
        if i not in visited:
            _dfsTopological(graph, i, visited, stack)
    stack.reverse()
    return stack

def generateTrie(strings):
    graph = {}
    graph['edges'] = []
    graph['adj'] = {}
    root = 1
    graph['adj'][root] = {}
    currNode = root
    for text in strings:
        root = 1
        found = True
        for s in text:
            if found:
                found = s in graph['adj'][root]
            if found:
                root = graph['adj'][root][s]
            else:
                currNode += 1
                graph['adj'][currNode] = {}
                graph['adj'][root][s] = currNode
                graph['edges'].append((root, currNode, s))
                root = currNode
    return graph['edges']

def _addEdge(adj, dna):
    k = len(dna)
    (a, b) = (dna[0:k-1], dna[1:k])
    found = False
    for t in adj:
        if t[0] == a  and  t[1] == b:
            found = True
            break
    if not found:
        adj.append((a, b, dna))
def deBruijn(dnas):
    adj = []
    for d in dnas:
        _addEdge(adj, d)
        _addEdge(adj, revComp(d))
    adj = sorted(adj)
    return adj

def ACGThist(dna):
    hist = {'A':0, 'C':0, 'G':0, 'T':0}
    for s in dna:
        hist[s] += 1
    return hist

def getLogProb(gcProb):
    logProb = {}
    atProb = math.log10((1 - gcProb) / 2)
    gcProb = math.log10(gcProb / 2)
    logProb['A'] = atProb
    logProb['T'] = atProb
    logProb['C'] = gcProb
    logProb['G'] = gcProb
    return logProb
