//
// Challenge name: Pangrams
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/37/
// Compile       : g++ -Wall -g -o Pangrams Pangrams.cpp
//

#include <stdio.h>
// assuming that line contains only 8192 characters
#define MAX_LINE 8192


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


int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    int i, j, len;
    int missing[26];
    char c;

    if(argc != 2) {
        printf("USAGE: Pangrams <fileContainingTestVectors>\n");
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
        for(i=0;i<26;i++) {
            missing[i] = 1;
        }
        for(i=0;i<len;i++) {
            c = currentLine[i];
            if((c >= 'A') && (c <= 'Z')) {
                c = c - 'A';
                missing[(int)c] = 0;
                continue;
            }
            if((c >= 'a') && (c <= 'z')) {
                c = c - 'a';
                missing[(int)c] = 0;
            }
        }
        j = 0;
        for(i=0;i<26;i++) {
            if(missing[i]) {
                printf("%c", (char)('a' + i));
                j++;
            }
        }
        if(j) {
            printf("\n");
        }
        else {
            printf("NULL\n");
        }
    }
    fclose(fp);
    return 0;
}
