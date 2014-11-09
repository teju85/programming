//
// Challenge name: JSON Menu IDs
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/102/
// Compile       : g++ -Wall -g -o JsonMenuIds JsonMenuIds.cpp
//

#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

#define MAX_LINE 1024

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

int str2num(const string& s) {
    stringstream ss(s);
    int pos;
    ss >> pos;
    return pos;
}

enum State {
    BRKT_OPEN,
    BRKT_CLOSE,
    KEY,
    VALUE,
    UNKNOWN
};

int sumOfIds(const char* str, int start, int len) {
    State s = BRKT_CLOSE;
    string currKey = "";
    string currVal = "";
    string idVal = "";
    bool labelFound = false;
    int idSum = 0;
    for(int i=start;i<len;++i) {
        if(str[i] ==  ']') {
            break;
        }
        if(str[i] == ' ') {
            continue;
        }
        if(str[i] == '{') {
            labelFound = false;
            currVal = "";
            currKey = "";
            idVal = "";
            s = KEY;
            continue;
        }
        if(str[i] == '}') {
            if(currKey == "\"id\"") {
                idVal = currVal;
            }
            if(labelFound && (idVal != "")) {
                idSum += str2num(idVal);
            }
            s = BRKT_CLOSE;
            continue;
        }
        if(s == BRKT_CLOSE) {
            continue;
        }
        if(str[i] == ':') {
            s = VALUE;
            if(currKey == "\"label\"") {
                labelFound = true;
            }
            continue;
        }
        if(str[i] == ',') {
            s = KEY;
            if(currKey == "\"id\"") {
                idVal = currVal;
            }
            currVal = "";
            currKey = "";
            continue;
        }
        if(s == KEY) {
            currKey += str[i];
        }
        else {
            currVal += str[i];
        }
    }
    return idSum;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: JsonMenuIds <fileContainingTestVectors>\n");
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
        int open = find(currentLine, 0, len, '[') + 1;
        if(open >= len) {
            printf("0\n");
            continue;
        }
        printf("%d\n", sumOfIds(currentLine, open, len));
    }
    fclose(fp);
    return 0;
}
