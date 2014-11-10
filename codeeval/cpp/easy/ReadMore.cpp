//
// Challenge name: Read More
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/167/
// Compile       : g++ -Wall -g -o ReadMore ReadMore.cpp
//

#include <stdio.h>
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

#define MAX_WITHOUT_TRIM 55
#define TRIMMED_LENGTH   40

void trim(char* line, int len) {
    if(len <= MAX_WITHOUT_TRIM) {
        printf("%s\n", line);
        return;
    }
    int pos = TRIMMED_LENGTH - 1;
    while((pos >= 0) && (line[pos] != ' ')) {
        --pos;
    }
    if(pos < 0) {
        pos = TRIMMED_LENGTH;
    }
    line[pos] = '\0';
    printf("%s... <Read More>\n", line);
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: ReadMore <fileContainingTestVectors>\n");
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
        trim(currentLine, len);
    }
    fclose(fp);
    return 0;
}
