//
// Challenge name: String Rotation
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/76/
// Compile       : g++ -Wall -g -o StringRotation StringRotation.cpp
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

int findComma(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] == ',') {
            return start;
        }
    }
    return start;
}

bool isRotation(char* str, int comma, int len) {
    char* str1 = str + comma + 1;
    int len1 = len - comma - 1;
    len = comma;
    //printf("len=%d len1=%d comma=%d\n", len, len1, comma);
    if(len1 != len) {
        return false;
    }
    for(int shift=0;shift<len;++shift) {
        bool match = true;
        for(int j=0;j<len;++j) {
            int k = j - shift;
            if(k < 0) {
                k = len + k;
            }
            //printf("k=%d shift=%d j=%d str=%c str1=%c\n", k, shift, j, str[j], str1[k]);
            if(str[j] != str1[k]) {
                match = false;
                break;
            }
        }
        if(match) {
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv) {
    FILE* fp;
    char line[MAX_LINE];
    if(argc != 2) {
        printf("USAGE: StringRotation <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        if(fscanf(fp, "%s", line) != 1) {
            continue;
        }
        int len = stringLen(line, MAX_LINE);
        int pos = findComma(line, 0, len);
        printf("%s\n", isRotation(line, pos, len)? "True" : "False");
    }
    fclose(fp);
    return 0;
}
