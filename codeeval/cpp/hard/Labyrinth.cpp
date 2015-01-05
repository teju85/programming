//
// Challenge name: Labyrinth
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/157/
// Compile       : g++ -Wall -g -o Labyrinth Labyrinth.cpp
//

#include <stdio.h>
#include <set>
#include <vector>
#include <string>
#include <queue>
#include <map>
#define MAX_LINE 256
using namespace std;

int stringLen(char* str, int max) {
    int i;
    for(i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            str[i] = '\0';
            return i;
        }
    }
    return max;
}


#define ROW_COL(r, c, node)                     \
    do {                                        \
        r = node / cols;                        \
        c = node % cols;                        \
    } while(0)
struct Labyrinth {
    void updateMaze(const char* str) {
        maze.push_back(str);
    }

    void findPath() {
        setup();
        bfs();
        markPath();
        printPath();
    }

private:
    void printPath() const {
        for(int i=0;i<rows;++i) {
            printf("%s\n", maze[i].c_str());
        }
    }

    void markPath() {
        int node = end;
        while(node != -1) {
            int r, c;
            ROW_COL(r, c, node);
            maze[r][c] = '+';
            map<int,int>::const_iterator itr = parent.find(node);
            node = (itr == parent.end())? -1 : itr->second;
        }
    }

    void setup() {
        rows = (int)maze.size();
        cols = (int)maze[0].size();
        for(int i=0;i<cols;++i) {
            if(isPath(0, i)) {
                start = i;
                break;
            }
        }
        for(int i=0;i<cols;++i) {
            if(isPath(rows-1, i)) {
                end = ((rows - 1) * cols) + i;
                break;
            }
        }
        frontier.push(start);
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
            //addNeighbor(node - cols - 1, node);
            addNeighbor(node - cols, node);
            //addNeighbor(node - cols + 1, node);
            addNeighbor(node - 1, node);
            addNeighbor(node + 1, node);
            //addNeighbor(node + cols - 1, node);
            addNeighbor(node + cols, node);
            //addNeighbor(node + cols + 1, node);
        }
    }

    void addNeighbor(int neigh, int node) {
        int r, c;
        ROW_COL(r, c, neigh);
        if(isPath(r, c) && !isVisited(neigh)) {
            frontier.push(neigh);
            parent[neigh] = node;
        }
    }

    bool isPath(int r, int c) const {
        return (maze[r][c] == ' ');
    }

    bool isVisited(int node) const {
        return (visited.find(node) != visited.end());
    }

    vector<string> maze;
    int rows, cols;
    int start, end;
    set<int> visited;
    queue<int> frontier;
    map<int,int> parent;
};
#undef ROW_COL


int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: Labyrinth <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    Labyrinth lab;
    while(!feof(fp)) {
        char currentLine[MAX_LINE];
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        int len = stringLen(currentLine, MAX_LINE);
        if(len <= 0) {
            continue;
        }
        lab.updateMaze(currentLine);
    }
    fclose(fp);
    lab.findPath();
    return 0;
}
