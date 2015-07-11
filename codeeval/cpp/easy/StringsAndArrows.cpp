//
// Challenge name: Strings And Arrows
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/203/
// Compile       : g++ -Wall -g -o StringsAndArrows StringsAndArrows.cpp
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

bool compare(const char* str1, const char* str2, int len) {
    for(int i=0;i<len;++i) {
        if(str1[i] != str2[i]) {
            return false;
        }
    }
    return true;
}

const char* arrow1 = ">>-->";
const char* arrow2 = "<--<<";
const int arrowLen = 5;

int arrows(const char* str, int len) {
    int count = 0;
    // forward
    int end = len - arrowLen;
    for(int i=0;i<=end;++i) {
        if(compare(str+i, arrow2, arrowLen)) {
            ++count;
        }
    }
    // backward
    for(int i=len;i>=arrowLen;--i) {
        if(compare(str+i-arrowLen, arrow1, arrowLen)) {
            ++count;
        }
    }
    return count;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: StringsAndArrows <fileContainingTestVectors>\n");
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
        printf("%d\n", arrows(currentLine, len));
    }
    fclose(fp);
    return 0;
}
