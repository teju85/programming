//
// Challenge name: Distinct Subsequences
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/69/
// Compile       : g++ -Wall -g -o DistinctSubsequences DistinctSubsequences.cpp
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

int find(char* str, int start, int len, char c) {
    for(;start<len;start++) {
        if(str[start] == c) {
            return start;
        }
    }
    return start;
}

int numDistinctSubsequences(char* s1, int len1, char* s2, int len2) {
    if(len1 < len2) {
        return 0;
    }
    if((len1 <= 0) || (len2 <= 0)) {
        return 0;
    }
    int num = 0;
    if(s1[0] == s2[0]) {
        if(len2 == 1) {
            ++num;
        }
        else {
            num += numDistinctSubsequences(s1+1, len1-1, s2+1, len2-1);
        }
    }
    num += numDistinctSubsequences(s1+1, len1-1, s2, len2);
    return num;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: DistinctSubsequences <fileContainingTestVectors>\n");
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
        int pos = find(currentLine, 0, len, ',');
        currentLine[pos] = '\0';
        printf("%d\n", numDistinctSubsequences(currentLine, pos, currentLine+pos+1, len-pos-1));
    }
    fclose(fp);
    return 0;
}
