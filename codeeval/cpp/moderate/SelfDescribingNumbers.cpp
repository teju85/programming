//
// Challenge name: Self Describing Numbers
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/40/
// Compile       : gcc -Wall -g -o SelfDescribingNumbers SelfDescribingNumbers.c
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
    int histogram[10];
    int i, len, val;

    if(argc != 2) {
        printf("USAGE: SelfDescribingNumbers <fileContainingTestVectors>\n");
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
        // histogram of each digit
        for(i=0;i<10;i++) {
            histogram[i] = 0;
        }
        for(i=0;i<len;i++) {
            val = (int) (currentLine[i] - '0'); // assuming all are digits!
            histogram[val]++;
        }
        // evaluate
        for(i=0;i<len;i++) {
            val = (int) (currentLine[i] - '0'); // assuming all are digits!
            if(histogram[i] != val) {
                break;
            }
        }
        printf("%d\n", (i < len)? 0 : 1);
    }
    fclose(fp);
    return 0;
}
