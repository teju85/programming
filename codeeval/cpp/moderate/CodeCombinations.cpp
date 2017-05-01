//
// Challenge name: CODE COMBINATIONS
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/238/
// Compile       : g++ -Wall -g -o CodeCombinations CodeCombinations.cpp
//

#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

void read(vector<string>& mat, FILE* fp) {
    char c, prev='\0';
    string s;
    while(!feof(fp)) {
        if(fscanf(fp, "%c", &c) != 1) {
            continue;
        }
        if(c == '\n') {
            break;
        }
        else if((c == ' ') && (prev != '|')) {
            mat.push_back(s);
            s.clear();
        } else if((c != ' ') && (c != '|')) {
            s.push_back(c);
        }
        prev = c;
    }
    if(s.size() > 0) {
        mat.push_back(s);
    }
}

void print(vector<string>& mat) {
    for(int i=0;i<(int)mat.size();++i) {
        printf("%s\n", mat[i].c_str());
    }
}

bool has(const vector<string>& mat, int r, int c) {
    bool hasC=false, hasO=false, hasD=false, hasE=false;
    for(int i=0;i<2;++i) {
        for(int j=0;j<2;++j) {
            switch(mat[r+i][j+c]) {
            case 'c': hasC = true; break;
            case 'o': hasO = true; break;
            case 'd': hasD = true; break;
            case 'e': hasE = true; break;
            default: break;
            }
        }
    }
    return (hasC && hasO && hasD && hasE);
}

int count(const vector<string>& mat) {
    int r = (int)mat.size();
    int c = (int)mat[0].size();
    int cnt = 0;
    for(int i=0;i<r-1;++i) {
        for(int j=0;j<c-1;++j) {
            cnt += has(mat, i, j);
        }
    }
    return cnt;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: CodeCombinations <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        vector<string> mat;
        read(mat, fp);
        if(mat.size() <= 0) {
            continue;
        }
        printf("%d\n", count(mat));
    }
    fclose(fp);
    return 0;
}
