//
// Challenge name: Longest Lines
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/2/
// Compile       : gcc -Wall -g -o LongestLines LongestLines.c
//

#include <stdio.h>
// assuming that line contains only 4096 characters
#define MAX_LINE 4096
#define NUM_LINES 256


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
    char line[NUM_LINES][MAX_LINE];
    int len[NUM_LINES], idx[NUM_LINES];
    int i, j, N, num, t;

    if(argc != 2) {
        printf("USAGE: LongestLines <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    num = 0;
    fscanf(fp, "%d", &N);
    while(!feof(fp)) {
        line[num][0] = '\0';
        fgets(line[num], MAX_LINE, fp);
        i = stringLen(line[num], MAX_LINE);
        if(i <= 0) {
            continue;
        }
        len[num] = i;
        idx[num] = num;
        num++;
    }
    fclose(fp);
    //@todo: use something else other than the bubble sort!
    for(i=0;i<num;i++) {
        for(j=i+1;j<num;j++) {
            if(len[i] < len[j]) {
                t = len[i];
                len[i] = len[j];
                len[j] = t;
                t = idx[i];
                idx[i] = idx[j];
                idx[j] = t;
            }
        }
    }
    t = (N < num)? N : num;
    for(i=0;i<t;i++) {
        printf("%s\n", line[idx[i]]);
    }
    return 0;
}
