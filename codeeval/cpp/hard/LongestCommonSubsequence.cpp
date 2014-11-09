//
// Challenge name: Longest Common Suquence
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/6/
// Compile       : g++ -Wall -g -o LongestCommonSubsequence LongestCommonSubsequence.cpp
//

#include <stdio.h>
#define MAX_LINE 512
#define MAX_STR 64

int matrix[MAX_STR][MAX_STR];

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

int find(const char* str, int start, int len, char c) {
    for(;start<len;start++) {
        if(str[start] == c) {
            return start;
        }
    }
    return start;
}

void evaluateLCS(char* str1, int len1, char* str2, int len2) {
    for(int i=0;i<=len1;++i) {
        matrix[i][0] = 0;
    }
    for(int j=0;j<=len2;++j) {
        matrix[0][j] = 0;
    }
    for(int i=1;i<=len1;++i) {
        for(int j=1;j<=len2;++j) {
            if(str1[i-1] == str2[j-1]) {
                matrix[i][j] = matrix[i-1][j-1] + 1;
            }
            else {
                int a = matrix[i][j-1];
                int b = matrix[i-1][j];
                matrix[i][j] = (a < b)? b : a;
            }
        }
    }
}

void printLCS(char* str1, int len1, int i, char* str2, int len2, int j) {
    if((i == 0) || (j == 0)) {
        return;
    }
    if(str1[i-1] == str2[j-1]) {
        printLCS(str1, len1, i-1, str2, len2, j-1);
        printf("%c", str1[i-1]);
    }
    else {
        if(matrix[i][j-1] > matrix[i-1][j]) {
            printLCS(str1, len1, i, str2, len2, j-1);
        }
        else {
            printLCS(str1, len1, i-1, str2, len2, j);
        }
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: LongestCommonSubsequence <fileContainingTestVectors>\n");
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
        int semi = find(currentLine, 0, len, ';');
        char* str1 = currentLine;
        int len1 = semi;
        char* str2 = currentLine + semi + 1;
        int len2 = len - semi - 1;
        evaluateLCS(str1, len1, str2, len2);
        printLCS(str1, len1, len1, str2, len2, len2);
        printf("\n");
    }
    fclose(fp);
    return 0;
}
