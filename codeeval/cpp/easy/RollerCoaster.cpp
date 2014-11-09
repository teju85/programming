//
// Challenge name: Roller Coaster
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/156/
// Compile       : g++ -Wall -g -o RollerCoaster RollerCoaster.cpp
//

#include <stdio.h>
#define MAX_LINE 1024

bool isLower(char c) {
    return ((c >= 'a') && (c <= 'z'));
}

bool isUpper(char c) {
    return ((c >= 'A') && (c <= 'Z'));
}

bool isAscii(char c) {
    return (isLower(c) || isUpper(c));
}

char toLower(char c) {
    if(isUpper(c)) {
        return (c - 'A' + 'a');
    }
    return c;
}

char toUpper(char c) {
    if(isLower(c)) {
        return (c - 'a' + 'A');
    }
    return c;
}

void rollerCoaster(char* str, int max) {
    int cap = 1;
    for(int i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            str[i] = '\0';
            break;
        }
        if(isAscii(str[i])) {
            str[i] = cap? toUpper(str[i]) : toLower(str[i]);
            ++cap;
            cap &= 0x1;
        }
    }
    printf("%s\n", str);
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: RollerCoaster <fileContainingTestVectors>\n");
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
        rollerCoaster(currentLine, MAX_LINE);
    }
    fclose(fp);
    return 0;
}
