//
// Challenge name: Guess The Number
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/170/
// Compile       : g++ -Wall -g -o GuessTheNumber GuessTheNumber.cpp
//

#include <stdio.h>
#include <string>
using namespace std;
#define MAX_LINE 4096

void _guess(int& lower, int& upper, const string& ss) {
    if(ss == "Lower") {
        upper = (upper + lower + 1) >> 1;
        upper -= 1;
    }
    else if(ss == "Higher") {
        lower = (upper + lower + 1) >> 1;
        lower += 1;
    }
    else if(ss == "Yay!") {
        upper = (upper + lower + 1) >> 1;
    }
}

int guess(int limit, char* str, int max) {
    int lower = 0;
    int upper = limit;
    string ss;
    for(int i=0;i<max;i++) {
        char c = str[i];
        if((c == '\n') || (c == '\r') || (c == '\0')) {
            _guess(lower, upper, ss);
            break;
        }
        if(c == ' ') {
            //printf("%d, %d  %s\n", lower, upper, ss.c_str());
            _guess(lower, upper, ss);
            //printf("%d, %d ---\n", lower, upper);
            ss.clear();
            continue;
        }
        ss += c;
    }
    return upper;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: GuessTheNumber <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    char currentLine[MAX_LINE];
    while(!feof(fp)) {
        int limit = -1;
        fscanf(fp, "%d", &limit);
        if(limit < 0) {
            continue;
        }
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        if(currentLine[0] == '\0') {
            continue;
        }
        printf("%d\n", guess(limit, currentLine, MAX_LINE));
    }
    fclose(fp);
    return 0;
}
