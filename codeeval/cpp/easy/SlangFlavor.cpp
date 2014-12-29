//
// Challenge name: Slang Flavor
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/174/
// Compile       : g++ -Wall -g -o SlangFlavor SlangFlavor.cpp
//

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
#define MAX_LINE 1024

int nextIdx = 0;
int evenCount = 1;
vector<string> slangs;

void fill() {
    slangs.push_back(", yeah!");
    slangs.push_back(", this is crazy, I tell ya.");
    slangs.push_back(", can U believe this?");
    slangs.push_back(", eh?");
    slangs.push_back(", aw yea.");
    slangs.push_back(", yo.");
    slangs.push_back("? No way!");
    slangs.push_back(". Awesome!");
}

void print(char* str, int max) {
    for(int i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            printf("\n");
            return;
        }
        if((str[i] == '.') || (str[i] == '!') || (str[i] == '?')) {
            if(evenCount) {
                printf("%c", str[i]);
                evenCount = 0;
                continue;
            }
            printf("%s", slangs[nextIdx].c_str());
            ++nextIdx;
            if(nextIdx >= (int)slangs.size()) {
                nextIdx = 0;
            }
            evenCount = 1;
            continue;
        }
        printf("%c", str[i]);
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: SlangFlavor <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    fill();
    while(!feof(fp)) {
        char currentLine[MAX_LINE];
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        if(currentLine[0] == '\0') {
            continue;
        }
        print(currentLine, MAX_LINE);
    }
    fclose(fp);
    return 0;
}
