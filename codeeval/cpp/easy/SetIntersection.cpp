//
// Challenge name: Set Intersection
// Difficulty    : easy
// Link          : http://codeeval.com/open_challenges/30/
// Compile       : g++ -Wall -g -o SetIntersection SetIntersection.cpp
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

int findSemiColon(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] == ';') {
            return start;
        }
    }
    return start;
}

int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    int arrA[MAX_INTS], arrB[MAX_INTS], inter[MAX_INTS];
    int i, j, numA, numB, len, semi, numI;

    if(argc != 2) {
        printf("USAGE: SetIntersection <fileContainingTestVectors>\n");
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
        numA = 0;
        for(i=0;i<semi;) {
            j = findNextComma(currentLine, i, semi);
            arrA[numA] = getInt(currentLine, i, j);
            numA++;
            i = j + 1;
        }
        numB = 0;
        for(i=semi+1;i<len;) {
            j = findNextComma(currentLine, i, len);
            arrB[numB] = getInt(currentLine, i, j);
            numB++;
            i = j + 1;
        }
        if((numA <= 0) || (numB <= 0)) {
            printf("\n");
            continue;
        }
        numI = 0;
        for(i=0,j=0;i<numA&&j<numB;) {
            if(arrA[i] < arrB[j]) {
                i++;
            }
            else if(arrA[i] > arrB[j]) {
                j++;
            }
            else {
                inter[numI] = arrA[i];
                numI++;
                i++;
                j++;
            }
        }
        if(numI <= 0) {
            printf("\n");
            continue;
        }
        printf("%d", inter[0]);
        for(i=1;i<numI;i++) {
            printf(",%d", inter[i]);
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
