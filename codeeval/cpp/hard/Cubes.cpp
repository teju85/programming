//
// Challenge name: Cubes
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/175/
// Compile       : g++ -Wall -g -o Cubes Cubes.cpp
//

#include <stdio.h>
#include <set>
#include <vector>
#include <string>
#include <queue>
#include <map>
using namespace std;
#define MAX_LINE 2048


#define ROW_COL_LEN(r, c, l, node)              \
    do {                                        \
        int tmp = node;                         \
        l = tmp / dim2;                         \
        tmp %= dim2;                            \
        r = tmp / dim;                          \
        c = tmp % dim;                          \
    } while(0)
struct Cube {
    Cube(const char* str, int d): dim(d), dim2(d*d), weights() {
        for(int i=0,idx=1;i<dim;++i) {
            vector<string> vec;
            for(int j=0;j<dim;++j,idx+=dim) {
                string s(str+idx,dim);
                vec.push_back(s);
            }
            maze.push_back(vec);
        }
    }

    int minPathLen() {
        setup();
        bfs();
        map<int,int>::const_iterator itr = weights.find(end);
        return ((itr == weights.end())? 0 : itr->second+1);
    }

private:
    void setup() {
        end = start = -1;
        for(int i=0;i<dim;++i) {
            if(isPath(0, i, 0)) {
                start = i;
                break;
            }
            if(isPath(i, 0, 0)) {
                start = i * dim;
                break;
            }
            if(isPath(dim-1, i, 0)) {
                start = ((dim-1)*dim) + i;
                break;
            }
            if(isPath(i, dim-1, 0)) {
                start = (i * dim) + dim - 1;
                break;
            }
        }
        int offset = dim2 * (dim - 1);
        for(int i=0;i<dim;++i) {
            if(isPath(0, i, dim-1)) {
                end = i;
                break;
            }
            if(isPath(i, 0, dim-1)) {
                end = i * dim;
                break;
            }
            if(isPath(dim-1, i, dim-1)) {
                end = ((dim-1)*dim) + i;
                break;
            }
            if(isPath(i, dim-1, dim-1)) {
                end = (i * dim) + dim - 1;
                break;
            }
        }
        end += offset;
        frontier.push(start);
        weights[start] = 0;
    }

    void bfs() {
        while(!frontier.empty()) {
            int node = frontier.front();
            frontier.pop();
            if(node == end) {
                break;
            }
            if(isVisited(node)) {
                continue;
            }
            visited.insert(node);
            addNeighbor(node - dim, node);
            addNeighbor(node - 1, node);
            addNeighbor(node + 1, node);
            addNeighbor(node + dim, node);
            addNeighborHole(node);
        }
    }

    void addNeighbor(int neigh, int node) {
        int r, c, l;
        ROW_COL_LEN(r, c, l, neigh);
        if(isVisited(neigh)) {
            return;
        }
        if(isPath(r, c, l)) {
            frontier.push(neigh);
            weights[neigh] = weights[node] + 1;
        }
    }

    void addNeighborHole(int node) {
        int r, c, l;
        int tmpNode = node - dim2;
        ROW_COL_LEN(r, c, l, tmpNode);
        if(isHole(r, c, l)) {
            addNeighbor(tmpNode, node);
        }
        tmpNode = node + dim2;
        ROW_COL_LEN(r, c, l, tmpNode);
        if(isHole(r, c, l)) {
            addNeighbor(tmpNode, node);
        }
    }

    bool isPath(int r, int c, int l) const {
        if((l < 0) || (l >= dim) || (r < 0) || (r >= dim) || (c < 0) || (c >= dim)) {
            return false;
        }
        return ((maze[l][r][c] == 'o') || (maze[l][r][c] == ' '));
    }

    bool isHole(int r, int c, int l) const {
        if((l < 0) || (l >= dim) || (r < 0) || (r >= dim) || (c < 0) || (c >= dim)) {
            return false;
        }
        return (maze[l][r][c] == 'o');
    }

    bool isVisited(int node) const {
        return (visited.find(node) != visited.end());
    }

    vector<vector<string> >  maze;
    int dim, dim2;
    int start, end;
    set<int> visited;
    queue<int> frontier;
    map<int,int> weights;
};
#undef ROW_COL_LEN


int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: Cubes <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int dim = -1;
        char currentLine[MAX_LINE];
        currentLine[0] = '\0';
        if(fscanf(fp, "%d", &dim) != 1) {
            continue;
        }
        fgets(currentLine, MAX_LINE, fp);
        if(currentLine[0] == '\0') {
            continue;
        }
        Cube c(currentLine, dim);
        printf("%d\n", c.minPathLen());
    }
    fclose(fp);
    return 0;
}
