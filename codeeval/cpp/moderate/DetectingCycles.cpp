//
// Challenge name: Detecting Cycles
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/5/
// Compile       : gcc -Wall -g -o DetectingCycles DetectingCycles.c
//

#include <stdio.h>
// assuming that line contains only 8192 characters
#define MAX_LINE 8192
// max number of integers in a line
#define MAX_INTS 1024


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

int getInt(char* str, int start, int end) {
    int i, factor, sum, sign;
    sign = 1;
    for(i=end-1,factor=1,sum=0;i>start;i--,factor*=10) {
        sum += (str[i] - '0') * factor;
    }
    if(str[start] == '-') {
        sign = -1;
    }
    else {
        sign = 1;
        sum += (str[start] - '0') * factor;
    }
    sum *= sign;
    return sum;
}

int findNextSpace(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] == ' ') {
            return start;
        }
    }
    return start;
}

int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    int nums[MAX_INTS];
    int i, j, k, len, num;

    if(argc != 2) {
        printf("USAGE: DetectingCycles <fileContainingTestVectors>\n");
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
        num = 0;
        for(i=0;i<len;) {
            j = findNextSpace(currentLine, i, len);
            nums[num] = getInt(currentLine, i, j);
            i = j + 1;
            num++;
        }
        if(num <= 0) {
            continue;
        }
        for(i=0;i<num;i++) {
            for(j=i+1;j<num;j++) {
                if(nums[i] == nums[j]) {
                    printf("%d", nums[i]);
                    for(k=i+1;k<j;k++) {
                        printf(" %d", nums[k]);
                    }
                    break;
                }
            }
            if(j < num) {
                break;
            }
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
