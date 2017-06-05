//
// Challenge name: Clean up the Words
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/205/
// Compile       : g++ -Wall -g -o CleanUpTheWords CleanUpTheWords.cpp
//

#include <stdio.h>
#define MAX_LINE 2048

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

bool isLower(char c) {
    return ((c >= 'a') && (c <= 'z'));
}

bool isUpper(char c) {
    return ((c >= 'A') && (c <= 'Z'));
}

bool isAlphabet(char c) {
    return (isLower(c) || isUpper(c));
}

char toLower(char c) {
    if(isLower(c)) {
        return c;
    }
    return ((c - 'A') + 'a');
}

enum States {
    ALPHABET,
    OTHER_CHAR
};

void cleanUp(const char* str, int len) {
    int numAlphabets = 0;
    States prevState = OTHER_CHAR;
    for(int i=0;i<len;++i) {
        if(isAlphabet(str[i])) {
            if((numAlphabets > 0) && (prevState == OTHER_CHAR)) {
                printf(" ");
            }
            prevState = ALPHABET;
            if(isLower(str[i])) {
                printf("%c", str[i]);
            }
            else {
                printf("%c", toLower(str[i]));
            }
            ++numAlphabets;
        }
        else {
            prevState = OTHER_CHAR;
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: CleanUpTheWords <fileContainingTestVectors>\n");
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
        cleanUp(currentLine, len);
    }
    fclose(fp);
    return 0;
}
