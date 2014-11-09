//
// Challenge name: String Searching
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/28/
// Compile       : g++ -Wall -g -o StringSearching StringSearching.cpp
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

int isLiteralStar(char* str, int len, int pos) {
    if((pos + 1) >= len) {
        return false;
    }
    if((str[pos] == '\\') && (str[pos+1] == '*')) {
        return true;
    }
    return false;
}

bool subStringMatch(char* str1, int len1, char* str2, int len2);

bool exactSubStringMatch(char* str1, int len1, char* str2, int len2) {
    if((len2 < 0) || (len1 <= 0)) {
        return false;
    }
    if(len2 == 0) {
        return true;
    }
    for(int i=0,j=0;i<len2&&j<len1;++i,++j) {
        if(isLiteralStar(str2, len2, i)) {
            ++i;
            if(str2[i] != str1[j]) {
                return false;
            }
            continue;
        }
        if(str2[i] == '*') {
            return subStringMatch(str1+j, len1-j, str2+i+1, len2-i-1);
        }
        if(str2[i] != str1[j]) {
            return false;
        }
    }
    return true;
}

bool subStringMatch(char* str1, int len1, char* str2, int len2) {
    if((len2 < 0) || (len1 <= 0)) {
        return false;
    }
    if(len2 == 0) {
        return true;
    }
    for(int i=0;i<len1;++i) {
        if(exactSubStringMatch(str1+i, len1-i, str2, len2)) {
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: StringSearching <fileContainingTestVectors>\n");
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
        int comma = find(currentLine, 0, len, ',');
        char* str1 = currentLine;
        currentLine[comma] = '\0';
        char* str2 = currentLine + comma + 1;
        printf("%s\n", subStringMatch(str1, comma, str2, len-comma-1)? "true" : "false");
    }
    fclose(fp);
    return 0;
}
