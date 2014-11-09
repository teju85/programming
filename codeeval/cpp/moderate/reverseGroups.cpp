//
// Challenge name: Reverse Groups
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/71/
// Compile       : g++ -Wall -g -o reverseGroups reverseGroups.cpp
//

#include <stdio.h>
#define MAX_LINE 4096
#define MAX_NUMBERS 8192

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
int findSemiColon(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] == ';') {
            return start;
        }
    }
    return start;
}

void reverseGroups(int* numbers, int num, int grp) {
    int limit = (num / grp) * grp;
    for(int i=0;i<limit;i+=grp) {
        int j = i + grp - 1;
        for(int k=i;k<j;++k,--j) {
            int temp = numbers[k];
            numbers[k] = numbers[j];
            numbers[j] = temp;
        }
    }
}

void printArray(int* numbers, int num) {
    if(num <= 0) {
        return;
    }
    printf("%d", numbers[0]);
    for(int i=1;i<num;++i) {
        printf(",%d", numbers[i]);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    int numbers[MAX_NUMBERS];
    int len, num, semi, grp;
    if(argc != 2) {
        printf("USAGE: reverseGroups <fileContainingTestVectors>\n");
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
        semi = findSemiColon(currentLine, 0, len);
        grp = getInt(currentLine, semi+1, len);
        num = 0;
        for(int i=0;i<semi;) {
            int j = findNextComma(currentLine, i, semi);
            numbers[num] = getInt(currentLine, i, j);
            num++;
            i = j + 1;
        }
        reverseGroups(numbers, num, grp);
        printArray(numbers, num);
    }
    fclose(fp);
    return 0;
}
