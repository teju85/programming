from common import generateAdjMatrix


def _putNamedNode(tree, name, weighted):
    tree['numV'] += 1
    if name != '':
        if weighted:
            tmp = name.split(':')
            n = tmp[0]
            w = int(tmp[1])
            tree['map'][n] = tree['numV']
            tree['rmap'][tree['numV']] = n
            tree['weights'][tree['numV']] = w
        else:
            tree['map'][name] = tree['numV']
            tree['rmap'][tree['numV']] = name

def _newickParse(line, start, tree, weighted):
    if start >= len(line):
        return start
    if line[start] != '(':
        return start
    start += 1
    nodes = []
    name = ''
    while start < len(line):
        char = line[start]
        if char == '(':
            start = _newickParse(line, start, tree, weighted)
            nodes.append(tree['root'])
        elif char == ',' or char == ')':
            start += 1
            _putNamedNode(tree, name, weighted)
            nodes.append(tree['numV'])
            name = ''
        else:
            name += char
            start += 1
        if char == ')':
            break
    root = ''
    while start < len(line):
        if line[start] in '(),;':
            break
        root += line[start]
        start += 1
    # you are done with the root node, so finish it!
    if start < len(line):
        if line[start] == ',':
            start += 1
    _putNamedNode(tree, root, weighted)
    tree['root'] = tree['numV']
    for n in nodes:
        tree['numE'] += 1
        if weighted:
            w = 0
            if n in tree['weights']:
                w = tree['weights'][n]
            tree['edges'].append((tree['root'], n, w))
        else:
            tree['edges'].append((tree['root'], n))
    return start

def newick(line, weighted=False):
    tree = {}
    tree['numV'] = 0
    tree['numE'] = 0
    tree['map'] = {}
    tree['rmap'] = {}
    tree['root'] = -1
    tree['edges'] = []
    if weighted:
        tree['weights'] = {}
    start = 0
    while start < len(line):
        start = _newickParse(line, start, tree, weighted)
        start += 1
    generateAdjMatrix(tree, weighted=weighted)
    return tree
