//
// Challenge name: Lowercase
// Difficulty    : easy
// Link          : http://www.codeeval.com/open_challenges/20/
// Compile       : gcc -Wall -g -o Lowercase Lowercase.c
//

#include <stdio.h>
// assuming that line contains only 4096 characters
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

int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    int i, len;
    char t;

    if(argc != 2) {
        printf("USAGE: ReverseWords <fileContainingTestVectors>\n");
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
        for(i=0;i<len;i++) {
            t = currentLine[i];
            if((t >= 'A') && (t <= 'Z')) {
                currentLine[i] = (t - 'A') + 'a';
            }
        }
        printf("%s\n", currentLine);
    }
    fclose(fp);
    return 0;
}
