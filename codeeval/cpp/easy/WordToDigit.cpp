//
// Challenge name: Word to Digit
// Difficulty    : easy
// Link          : [2;2~https://www.codeeval.com/open_challenges/104/
// Compile       : g++ -Wall -g -o WordToDigit WordToDigit.cpp
//

#include <stdio.h>
#include <map>
#include <string>
#include <string.h>
// assuming that line contains only 8192 characters
#define MAX_LINE 8192
using namespace std;

map<string, int> words;

void initMap() {
    words["zero"] = 0;
    words["one"] = 1;
    words["two"] = 2;
    words["three"] = 3;
    words["four"] = 4;
    words["five"] = 5;
    words["six"] = 6;
    words["seven"] = 7;
    words["eight"] = 8;
    words["nine"] = 9;
}

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

int findSemiColon(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] == ';') {
            return start;
        }
    }
    return start;
}

int wordToDigit(char* str, int start, int end) {
    string s(str+start, end-start);
    if(words.find(s) == words.end()) {
        return -1;
    }
    return words[s];
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: WordToDigit <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    initMap();
    while(!feof(fp)) {
        char currentLine[MAX_LINE];
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        int len = stringLen(currentLine, MAX_LINE);
        if(len <= 0) {
            continue;
        }
        int start = 0;
        int semi = 0;
        while(semi < len) {
            semi = findSemiColon(currentLine, start, len);
            printf("%d", wordToDigit(currentLine, start, semi));
            start = semi + 1;
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
