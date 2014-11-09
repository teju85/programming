//
// Challenge name: Word Chain
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/135/
// Compile       : g++ -Wall -g -o WordChain WordChain.cpp
//

#include <stdio.h>
#include <vector>
#include <string>
using namespace std;
#define MAX_LINE 512

void getVector(char* str, int max, vector<string>& arr) {
    string ss;
    int i;
    for(i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            break;
        }
        if(str[i] == ',') {
            arr.push_back(ss);
            ss.clear();
            continue;
        }
        ss += str[i];
    }
    if(ss.size() > 0) {
        arr.push_back(ss);
    }
}

struct MaxPath {
    MaxPath(const vector<string>& arr): size((int)arr.size()), visited(), adj(NULL) {
        adj = new bool*[size];
        for(int i=0;i<size;++i) {
            adj[i] = new bool[size];
            visited.push_back(false);
        }
        for(int i=0;i<size;++i) {
            adj[i][i] = false;
            for(int j=i+1;j<size;++j) {
                adj[i][j] = isChain(arr[i], arr[j]);
                adj[j][i] = isChain(arr[j], arr[i]);
            }
        }
    }
    ~MaxPath() {
        for(int i=0;i<size;++i) {
            delete [] adj[i];
        }
        delete [] adj;
    }
    int findMaxPathLen() {
        int max = -1;
        for(int i=0;i<size;++i) {
            visited[i] = true;
            int m = _findDepth(i) + 1;
            if(m > max) {
                max = m;
            }
            visited[i] = false;
        }
        return max;
    }
private:
    int size;
    vector<bool> visited;
    bool** adj;
    int _findDepth(int node) {
        int maxDepth = 0;
        for(int i=0;i<size;++i) {
            if(adj[node][i] && !visited[i]) {
                visited[i] = true;
                int d = _findDepth(i) + 1;
                if(d > maxDepth) {
                    maxDepth = d;
                }
                visited[i] = false;
            }
        }
        return maxDepth;
    }
    bool isChain(const string& a, const string& b) const {
        if(a[a.size()-1] == b[0]) {
            return true;
        }
        return false;
    }
    bool allVisited() {
        for(int i=0;i<size;++i) {
            if(!visited[i]) {
                return false;
            }
        }
        return true;
    }
};

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: WordChain <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        char currentLine[MAX_LINE];
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        if(currentLine[0] == '\0') {
            continue;
        }
        vector<string> arr;
        getVector(currentLine, MAX_LINE, arr);
        MaxPath m(arr);
        int len = m.findMaxPathLen();
        if(len <= 1) {
            printf("None\n");
        }
        else {
            printf("%d\n", len);
        }
    }
    fclose(fp);
    return 0;
}
