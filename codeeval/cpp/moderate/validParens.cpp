//
// Challenge name: Valid Parentheses
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/68/
// Compile       : g++ -Wall -g -o validParens validParens.cpp
//

#include <stdio.h>
#include <vector>
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

bool isOpenParen(char c) {
    return ((c == '(') || (c == '{') || (c == '['));
}

bool isCloseParen(char c) {
    return ((c == ')') || (c == '}') || (c == ']'));
}

bool openCloseParensMatch(char open, char close) {
    if((open == '(') && (close == ')')) return true;
    if((open == '{') && (close == '}')) return true;
    if((open == '[') && (close == ']')) return true;
    return false;
}

bool isValidParens(char* line, int len) {
    vector<char> stack;
    for(int i=0;i<len;++i) {
        if(isOpenParen(line[i])) {
            stack.push_back(line[i]);
        }
        else if(isCloseParen(line[i])) {
            if(stack.empty()) {
                return false;
            }
            char lastOpenParen = stack.back();
            if(!openCloseParensMatch(lastOpenParen, line[i])) {
                return false;
            }
            stack.pop_back();
        }
        else {
            return false;
        }
    }
    return stack.empty();
}

int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    int len;
    if(argc != 2) {
        printf("USAGE: validParens <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        len = stringLen(currentLine, MAX_LINE);
        if(len <= 0) {
            continue;
        }
        printf("%s\n", isValidParens(currentLine, len)? "True" : "False");
    }
    fclose(fp);
    return 0;
}
