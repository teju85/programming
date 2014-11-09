//
// Challenge name: Beautiful Strings
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/83/
// Compile       : g++ -Wall -g -o BeautifulStrings BeautifulStrings.cpp
//

#include <stdio.h>
#include <ctype.h>
#define MAX_LINE 1024
#define NUM_CHARS 26

int charHist[NUM_CHARS];

void initHist() {
    for(int i=0;i<NUM_CHARS;++i) {
        charHist[i] = 0;
    }
}

void populateHist(char* str, int max) {
    for(int i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            break;
        }
        if(isalpha(str[i])) {
            int pos = tolower(str[i]) - 'a';
            ++charHist[pos];
        }
    }
}

int calculateBeauty() {
    int totalBeauty = 0;
    int beauty = NUM_CHARS;
    for(int i=0;i<NUM_CHARS;++i) {
        for(int j=i+1;j<NUM_CHARS;++j) {
            if(charHist[i] < charHist[j]) {
                int t = charHist[i];
                charHist[i] = charHist[j];
                charHist[j] = t;
            }
        }
        if(charHist[i] <= 0) {
            break;
        }
        totalBeauty += (beauty * charHist[i]);
        --beauty;
    }
    return totalBeauty;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: BeautifulStrings <fileContainingTestVectors>\n");
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
        if(currentLine[0] == '\0') {
            continue;
        }
        initHist();
        populateHist(currentLine, MAX_LINE);
        printf("%d\n", calculateBeauty());
    }
    fclose(fp);
    return 0;
}
