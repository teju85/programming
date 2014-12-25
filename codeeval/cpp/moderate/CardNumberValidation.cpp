//
// Challenge name: Card Number Validation
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/172/
// Compile       : g++ -Wall -g -o CardNumberValidation CardNumberValidation.cpp
//

#include <stdio.h>
#define MAX_LINE 32

int char2num(char c) {
    return (int)(c - '0');
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

int doubleNum(int val) {
    if(val < 5) {
        return (2 * val);
    }
    val *= 2;
    val = (val / 10) + (val % 10);
    return val;
}

int isValid(char* str, int len) {
    int sum = char2num(str[len-1]);
    int prevDouble = 0;
    for(int i=len-2;i>=0;--i) {
        char c = str[i];
        if(c == ' ') {
            continue;
        }
        int val = char2num(c);
        if(prevDouble) {
            sum += val;
            prevDouble = 0;
        }
        else {
            sum += doubleNum(val);
            prevDouble = 1;
        }
    }
    return ((sum % 10) == 0);
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: CardNumberValidation <fileContainingTestVectors>\n");
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
        printf("%d\n", isValid(currentLine, len));
    }
    fclose(fp);
    return 0;
}
