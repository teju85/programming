//
// Challenge name: Gronsfeld Cipher
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/181/
// Compile       : g++ -Wall -g -o GronsfeldCipher GronsfeldCipher.cpp
//

#include <stdio.h>
#define MAX_LINE 4096

const char str[] = " !\"#$%&'()*+,-./0123456789:<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const int strLen = sizeof(str) / sizeof(char);

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

int findNextColon(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] == ';') {
            return start;
        }
    }
    return start;
}

int findCharPos(char elem) {
    for(int i=0;i<strLen;++i) {
        if(str[i] == elem) {
            return i;
        }
    }
    return -1;
}

char decodeChar(char c, char s) {
    int pos = findCharPos(c);
    int shift = (int)(s - '0');
    pos -= shift;
    if(pos < 0) {
        pos = strLen + pos - 1;
    }
    return str[pos];
}

void decode(char* str, int len) {
    int colon = findNextColon(str, 0, len);
    char* shifts = str;
    int slen = colon;
    char* code = str + colon + 1;
    int clen = len - colon - 1;
    for(int i=0,j=0;i<clen;++i,++j) {
        if(j == slen) {
            j = 0;
        }
        char t = decodeChar(code[i], shifts[j]);
        if(t == '\n') {
            printf("\\n");
        }
        else {
            printf("%c", t);
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: GronsfeldCipher <fileContainingTestVectors>\n");
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
        decode(currentLine, len);
    }
    fclose(fp);
    return 0;
}
