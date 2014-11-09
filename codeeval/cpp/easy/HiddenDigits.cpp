//
// Challenge name: Hidden Digits
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/122/
// Compile       : g++ -Wall -g -o HiddenDigits HiddenDigits.cpp
//

#include <stdio.h>
#define MAX_LINE 2048


void printHiddenVisible(char* str, int max) {
    int num = 0;
    for(int i=0;i<max;i++) {
        char c = str[i];
        if((c == '\n') || (c == '\r') || (c == '\0')) {
            break;
        }
	if((c >= '0') && (c <= '9')) {
            ++num;
            printf("%c", c);
            continue;
        }
        switch(c) {
        case 'a': printf("0"); ++num; break;
        case 'b': printf("1"); ++num; break;
        case 'c': printf("2"); ++num; break;
        case 'd': printf("3"); ++num; break;
        case 'e': printf("4"); ++num; break;
        case 'f': printf("5"); ++num; break;
        case 'g': printf("6"); ++num; break;
        case 'h': printf("7"); ++num; break;
        case 'i': printf("8"); ++num; break;
        case 'j': printf("9"); ++num; break;
        default : break;
        }
    }
    if(num == 0) {
        printf("NONE");
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: HiddenDigits <fileContainingTestVectors>\n");
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
	printHiddenVisible(currentLine, MAX_LINE);
    }
    fclose(fp);
    return 0;
}
