//
// Challenge name: Big Digits
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/163/
// Compile       : g++ -Wall -g -o BigDigits BigDigits.cpp
//

#include <stdio.h>
#define MAX_LINE 64
#include <vector>
using namespace std;

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

bool isdigit(char c) {
    return ((c >= '0') && (c <= '9'));
}

int char2digit(char c) {
    return (int)(c - '0');
}

#define ROWS  6
#define COLS  64
#define WIDTH 5
char matrix[ROWS][COLS] = {"-**----*--***--***---*---****--**--****--**---**--",
                           "*--*--**-----*----*-*--*-*----*-------*-*--*-*--*-",
                           "*--*---*---**---**--****-***--***----*---**---***-",
                           "*--*---*--*-------*----*----*-*--*--*---*--*----*-",
                           "-**---***-****-***-----*-***---**---*----**---**--",
                           "--------------------------------------------------"};

void bigDigits(char* str, int len) {
    vector<int> arr;
    for(int i=0;i<len;++i) {
        if(!isdigit(str[i])) {
            continue;
        }
        arr.push_back(char2digit(str[i]));
    }
    for(int i=0;i<ROWS;++i) {
        for(vector<int>::const_iterator itr=arr.begin();itr!=arr.end();++itr) {
            int start = *itr * WIDTH;
            for(int k=0;k<WIDTH;++k) {
                printf("%c", matrix[i][start+k]);
            }
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: BigDigits <fileContainingTestVectors>\n");
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
        bigDigits(currentLine, len);
    }
    fclose(fp);
    return 0;
}
