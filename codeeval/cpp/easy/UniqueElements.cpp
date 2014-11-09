//
// Challenge name: Unique Elements
// Difficulty    : easy
// Link          : http://codeeval.com/open_challenges/29/
// Compile       : g++ -Wall -g -o UniqueElements UniqueElements.cpp
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
    int i, factor, sum;
    for(i=end-1,factor=1,sum=0;i>=start;i--,factor*=10) {
        sum += (str[i] - '0') * factor;
    }
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

int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    int arr[MAX_INTS];
    int i, j, numInts, len;

    if(argc != 2) {
        printf("USAGE: UniqueElements <fileContainingTestVectors>\n");
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
        numInts = 0;
        for(i=0;i<len;) {
            j = findNextComma(currentLine, i, len);
            arr[numInts] = getInt(currentLine, i, j);
            numInts++;
            i = j + 1;
        }
        if(numInts <= 0) {
            continue;
        }
        printf("%d", arr[0]);
        j = arr[0];
        for(i=1;i<numInts;i++) {
            if(j != arr[i]) { // next unique number found!
                j = arr[i];
                printf(",%d", j);
            }
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
