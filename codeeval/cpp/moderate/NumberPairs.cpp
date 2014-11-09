//
// Challenge name: Number Pairs
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/34/
// Compile       : g++ -Wall -g -o NumberPairs NumberPairs.cpp
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

int isUniquePair(int pairs[][MAX_INTS], int numP, int a, int b) {
    int i;
    for(i=0;i<numP;i++) {
        if((pairs[0][i] == a) && (pairs[1][i] == b)) {
            return 0;
        }
        if(pairs[0][i] > a) {
            return 1;
        }
    }
    return 1;
}

int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    int arr[MAX_INTS], pairs[2][MAX_INTS];
    int i, j, num, numP, X, len, semi;

    if(argc != 2) {
        printf("USAGE: NumberPairs <fileContainingTestVectors>\n");
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
        num = 0;
        for(i=0;i<semi;) {
            j = findNextComma(currentLine, i, semi);
            arr[num] = getInt(currentLine, i, j);
            num++;
            i = j + 1;
        }
        if(num <= 0) {
            continue;
        }
        X = getInt(currentLine, semi+1, len);
        if((arr[num-1] + arr[num-2]) < X) {
            printf("NULL\n");
            continue;
        }
        if((arr[0] + arr[1]) > X) {
            printf("NULL\n");
            continue;
        }
        numP = 0;
        for(i=0;i<num;i++) {
            for(j=i+1;j<num;j++) {
                if((arr[i] + arr[j]) == X) {
                    if(isUniquePair(pairs, numP, arr[i], arr[j])) {
                        pairs[0][numP] = arr[i];
                        pairs[1][numP] = arr[j];
                        numP++;
                        break;
                    }
                }
            }
        }
        if(numP <= 0) {
            printf("NULL\n");
            continue;
        }
        printf("%d,%d", pairs[0][0], pairs[1][0]);
        for(i=1;i<numP;i++) {
            printf(";%d,%d", pairs[0][i], pairs[1][i]);
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
