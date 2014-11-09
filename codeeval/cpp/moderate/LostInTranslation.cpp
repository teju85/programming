//
// Challenge name: Lost In Translation
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/121/
// Compile       : g++ -Wall -g -o LostInTranslation LostInTranslation.cpp
//

#include <stdio.h>
#include <map>
#define MAX_LINE 1024

using namespace std;

map<char,char> reverseMap;

void initMap() {
    reverseMap['y'] = 'a';
    reverseMap['n'] = 'b';
    reverseMap['f'] = 'c';
    reverseMap['i'] = 'd';
    reverseMap['c'] = 'e';
    reverseMap['w'] = 'f';
    reverseMap['l'] = 'g';
    reverseMap['b'] = 'h';
    reverseMap['k'] = 'i';
    reverseMap['u'] = 'j';
    reverseMap['o'] = 'k';
    reverseMap['m'] = 'l';
    reverseMap['x'] = 'm';
    reverseMap['s'] = 'n';
    reverseMap['e'] = 'o';
    reverseMap['v'] = 'p';
    reverseMap['z'] = 'q';
    reverseMap['p'] = 'r';
    reverseMap['d'] = 's';
    reverseMap['r'] = 't';
    reverseMap['j'] = 'u';
    reverseMap['g'] = 'v';
    reverseMap['t'] = 'w';
    reverseMap['h'] = 'x';
    reverseMap['a'] = 'y';
    reverseMap['q'] = 'z';
}

void convert(char* str, int max) {
    for(int i=0;i<max;i++) {
        char c = str[i];
        if((c == '\n') || (c == '\r') || (c == '\0')) {
            break;
        }
        if(c == ' ') {
            printf(" ");
            continue;
        }
        printf("%c", reverseMap[c]);
    }
    printf("\n");
    return;
}

int main(int argc, char** argv) {
    initMap();
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: LostInTranslation <fileContainingTestVectors>\n");
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
	convert(currentLine, MAX_LINE);
    }
    fclose(fp);
    return 0;
}
