//
// Challenge name: Find Writer
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/97/
// Compile       : g++ -Wall -g -o FindWriter FindWriter.cpp
//

#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

#define MAX_LINE 4096

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

int find(char* str, int start, int len, char c) {
    for(;start<len;start++) {
        if(str[start] == c) {
            return start;
        }
    }
    return start;
}

void printChar(const string& num, const char* str) {
    stringstream s(num);
    int pos;
    s >> pos;
    --pos;
    printf("%c", str[pos]);
}

void decodeWriter(const char* str, int start, int len) {
    string num = "";
    for(int i=start;i<len;++i) {
        if(str[i] == ' ') {
            printChar(num, str);
            num = "";
            continue;
        }
        num += str[i];
    }
    if(num != "") {
        printChar(num, str);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: FindWriter <fileContainingTestVectors>\n");
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
        int len = stringLen(currentLine, MAX_LINE);
        if(len <= 0) {
            continue;
        }
        int pipe = find(currentLine, 0, len, '|') + 2;  // that's where the first digit starts!
        decodeWriter(currentLine, pipe, len);
    }
    fclose(fp);
    return 0;
}
