//
// Challenge name: Telephone Words
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/59/
// Compile       : g++ -Wall -g -o TelephoneWords TelephoneWords.cpp
//

#include <stdio.h>

#define NUMD 10
#define MAXC 5
#define MAXD 7

char words[NUMD][MAXC] = {
    {'0', '\0', '\0', '\0', '\0'},
    {'1', '\0', '\0', '\0', '\0'},
    {'a',  'b',  'c', '\0', '\0'},
    {'d',  'e',  'f', '\0', '\0'},
    {'g',  'h',  'i', '\0', '\0'},
    {'j',  'k',  'l', '\0', '\0'},
    {'m',  'n',  'o', '\0', '\0'},
    {'p',  'q',  'r',  's', '\0'},
    {'t',  'u',  'v', '\0', '\0'},
    {'w',  'x',  'y',  'z', '\0'}
};

bool firstWord;
int numLetters;
char digits[MAXD];
char str[MAXD];

int char2digit(char c) {
    return (int)(c - '0');
}

void printTelephoneWords(int start=0) {
    if(start == numLetters) {
        if(!firstWord) {
            printf(",");
        }
        for(int i=0;i<numLetters;++i) {
            printf("%c", str[i]);
        }
        firstWord = false;
        return;
    }
    int d = char2digit(digits[start]);
    char* letters = words[d];
    while(*letters != '\0') {
        str[start] = *letters;
        printTelephoneWords(start+1);
        ++letters;
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: TelephoneWords <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        numLetters = 0;
        firstWord = true;
        do {
            if(feof(fp)) {
                break;
            }
            fscanf(fp, "%c", &(digits[numLetters]));
            ++numLetters;
        } while(digits[numLetters-1] != '\n');
        --numLetters;
        if(numLetters <= 0) {
            break;
        }
        printTelephoneWords();
        printf("\n");
    }
    fclose(fp);
    return 0;
}
