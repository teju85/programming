//
// Challenge name: Balanced Smileys
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/84/
// Compile       : g++ -Wall -g -o BalancedSmileys BalancedSmileys.cpp
//

#include <stdio.h>
#define MAX_LINE 1024

bool isEnd(char c) {
    return ((c == '\n') || (c == '\r') || (c =='\0'));
}

bool isBalanced(char* str, int numOpenParens=0) {
    if(isEnd(str[0])) {
        return (numOpenParens == 0);
    }
    if(str[0] == '(') {
        ++numOpenParens;
        return isBalanced(str+1, numOpenParens);
    }
    if(str[0] == ')') {
        if(numOpenParens <= 0) {
            return false;
        }
        --numOpenParens;
        return isBalanced(str+1, numOpenParens);
    }
    if(((str[0] >= 'a') && (str[0] <= 'z')) || (str[0] == ' ')) {
        return isBalanced(str+1, numOpenParens);
    }
    if(str[0] == ':') {
        if(isBalanced(str+1, numOpenParens)) {
            return true;
        }
        if(!isEnd(str[1])) {
            if(str[1] == ')') {
                return isBalanced(str+2, numOpenParens);
            }
            else if(str[1] == '(') {
                return isBalanced(str+2, numOpenParens);
            }
        }
        return false;
    }
    return (numOpenParens == 0);
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: BalancedSmileys <fileContainingTestVectors>\n");
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
        printf("%s\n", isBalanced(currentLine)? "YES" : "NO");
    }
    fclose(fp);
    return 0;
}
