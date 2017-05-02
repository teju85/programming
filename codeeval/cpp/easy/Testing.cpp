//
// Challenge name: TESTING
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/225/
// Compile       : g++ -Wall -g -o Testing Testing.cpp
//

#include <stdio.h>
#define MAX_LINE 512

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

const char* tag(int nBugs) {
    if(nBugs == 0) return "Done";
    if(nBugs <= 2) return "Low";
    if(nBugs <= 4) return "Medium";
    if(nBugs <= 6) return "High";
    return "Critical";
}

int countBugs(const char* str, int len) {
    // Heelo Codevval | Hello Codeeval
    // ^ first          ^ second
    int sLen = (len - 3) >> 1;
    const char* first = str;
    const char* second = str + sLen + 3;
    int cnt = 0;
    for(int i=0;i<sLen;++i) {
        cnt += (first[i] != second[i]);
    }
    return cnt;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: Testing <fileContainingTestVectors>\n");
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
        int nBugs = countBugs(currentLine, len);
        printf("%s\n", tag(nBugs));
    }
    fclose(fp);
    return 0;
}
