//
// Challenge name: Decode Numbers
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/73/
// Compile       : g++ -Wall -g -o decodeNumbers decodeNumbers.cpp
//

#include <stdio.h>

#define MAX_LINE 4096

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

int char2int(char c) {
    return (int)(c - '0');
}

int char2int(char c1, char c2) {
    return ((char2int(c1) * 10) + char2int(c2));
}

bool isValidDecode(char c) {
    int val = char2int(c);
    return ((val >= 1) && (val <= 26));
}

bool isValidDecode(char c1, char c2) {
    int val = char2int(c1, c2);
    return ((val >= 1) && (val <= 26));
}

void numWaysToDecode(char* encode, int len, int start, int& numDecodes) {
    // reached the end
    if(start >= len) {
        numDecodes++;
        return;
    }
    if(isValidDecode(encode[start])) {
        numWaysToDecode(encode, len, start+1, numDecodes);
    }
    if((start <= len-2) && isValidDecode(encode[start], encode[start+1])) {
        numWaysToDecode(encode, len, start+2, numDecodes);
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    char encode[MAX_LINE];
    int len;
    if(argc != 2) {
        printf("USAGE: decodeNumbers <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        encode[0] = '\0';
        fgets(encode, MAX_LINE, fp);
        len = stringLen(encode, MAX_LINE);
        if(len <= 0) {
            continue;
        }
        int numDecodes = 0;
        numWaysToDecode(encode, len, 0, numDecodes);
        printf("%d\n", numDecodes);
    }
    fclose(fp);
    return 0;
}
