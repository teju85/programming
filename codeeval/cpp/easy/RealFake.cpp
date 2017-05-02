//
// Challenge name: REAL FAKE
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/227/
// Compile       : g++ -Wall -g -o RealFake RealFake.cpp
//

#include <stdio.h>
#define MAX_LINE 32

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

bool isReal(const char* str, int len) {
    int sum = 0;
    for(int i=0,j=0;i<len;++i) {
        if(str[i] == ' ') continue;
        if(j & 1) {
            int odd = (int)(str[i] - '0');
            sum += odd;
        } else {
            int even = ((int)(str[i] - '0')) * 2;
            sum += even;
        }
        ++j;
    }
    return ((sum % 10) == 0);
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: RealFake <fileContainingTestVectors>\n");
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
        printf("%s\n", isReal(currentLine, len)? "Real" : "Fake");
    }
    fclose(fp);
    return 0;
}
