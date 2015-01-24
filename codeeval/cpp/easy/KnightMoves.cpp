//
// Challenge name: Knight Moves
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/180/
// Compile       : g++ -Wall -g -o KnightMoves KnightMoves.cpp
//

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

void addMove(char r, char c, vector<string>& out) {
    if((r < 'a') || (r > 'h')) {
        return;
    }
    if((c < '1') || (c > '8')) {
        return;
    }
    string s;
    s += r;
    s += c;
    out.push_back(s);
}

vector<string> getNextMoves(char row, char col) {
    vector<string> out;
    addMove(row+2, col+1, out);
    addMove(row+1, col+2, out);
    addMove(row-1, col+2, out);
    addMove(row-2, col+1, out);
    addMove(row-2, col-1, out);
    addMove(row-1, col-2, out);
    addMove(row+1, col-2, out);
    addMove(row+2, col-1, out);
    sort(out.begin(), out.end());
    return out;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: KnightMoves <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    char buff[8];
    while(!feof(fp)) {
        if(fscanf(fp, "%s", buff) != 1) {
            continue;
        }
        vector<string> out = getNextMoves(buff[0], buff[1]);
        vector<string>::const_iterator i = out.begin();
        printf("%s", i->c_str());
        for(++i;i!=out.end();++i) {
            printf(" %s", i->c_str());
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
