//
// Challenge name: Game Of Life
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/161/
// Compile       : g++ -Wall -g -o GameOfLife GameOfLife.cpp
//

#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

#define MAX_LINE 128
#define NUM_ITERATIONS 10

void print(const vector<string>& mat) {
    for(vector<string>::const_iterator i=mat.begin();i!=mat.end();++i) {
        printf("%s", i->c_str());
    }
}

bool isAlive(vector<string>& src, int i, int j) {
    return (src[i][j] == '*');
}

void updateNeighborCounts(vector<vector<int> >& count, int i, int j) {
    for(int x=-1;x<=1;++x) {
        for(int y=-1;y<=1;++y) {
            count[i+x][j+y]++;
        }
    }
    count[i][j]--;
}

void updateCounts(vector<string>& src, vector<vector<int> >& count, int N) {
    int N2 = N + 2;
    for(int i=0;i<N2;++i) {
        for(int j=0;j<N2;++j) {
            count[i][j] = 0;
        }
    }
    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j) {
            if(isAlive(src, i, j)) {
                updateNeighborCounts(count, i+1, j+1);
            }
        }
    }
    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j) {
            if(isAlive(src, i, j)) {
                if(count[i+1][j+1] < 2) {
                    src[i][j] = '.';
                }
                else if(count[i+1][j+1] <= 3) {
                }
                else {
                    src[i][j] = '.';
                }
            }
            else {
                if(count[i+1][j+1] == 3) {
                    src[i][j] = '*';
                }
            }
        }
    }
}

void gameOfLife(vector<string>& mat) {
    int N = (int)mat.size();  // assumes square matrix!
    vector<vector<int> > count(N+2, vector<int>(N+2));
    for(int iter=1;iter<=NUM_ITERATIONS;++iter) {
        updateCounts(mat, count, N);
    }
    print(mat);
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: GameOfLife <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    vector<string> mat;
    while(!feof(fp)) {
        char currentLine[MAX_LINE];
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        if(currentLine[0] == '\0') {
            continue;
        }
        mat.push_back(currentLine);
    }
    fclose(fp);
    gameOfLife(mat);
    return 0;
}
