//
// Challenge name: Sum to Zero
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/81/
// Compile       : g++ -Wall -g -o sumToZero sumToZero.cpp
//

#include <stdio.h>
#define MAX_LINE 4096
#define MAX_NUMBERS 8192
#define NUM_ELEMENTS 4

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
    int i, factor, sum;
    int minus = 1;
    if(str[start] == '-') {
        minus = -1;
        ++start;
    }
    for(i=end-1,factor=1,sum=0;i>=start;i--,factor*=10) {
        sum += (str[i] - '0') * factor;
    }
    sum *= minus;
    return sum;
}

int findNextComma(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] == ',') {
            return start;
        }
    }
    return start;
}

int countSumToZero(int* numbers, int len) {
    int count = 0;
    for(int x=0;x<len;++x) {
        for(int y=x+1;y<len;++y) {
            for(int z=y+1;z<len;++z) {
                for(int w=z+1;w<len;++w) {
                    int sum = numbers[x] + numbers[y] + numbers[z] + numbers[w];
                    if(sum == 0) {
                        ++count;
                    }
                }
            }
        }
    }
    return count;
}

int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    int numbers[MAX_NUMBERS];
    int len, num;
    if(argc != 2) {
        printf("USAGE: sumToZero <fileContainingTestVectors>\n");
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
        for(int i=0;i<len;) {
            int j = findNextComma(currentLine, i, len);
            numbers[num] = getInt(currentLine, i, j);
            num++;
            i = j + 1;
        }
        printf("%d\n", countSumToZero(numbers, num));
    }
    fclose(fp);
    return 0;
}
