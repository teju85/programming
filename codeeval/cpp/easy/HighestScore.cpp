//
// Challenge name: Highest Score
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/208
// Compile       : g++ -Wall -g -o HighestScore HighestScore.cpp
//

#include <stdio.h>
#define MAX_LINE 2048
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int str2num(const string& s) {
    stringstream ss(s);
    int pos;
    ss >> pos;
    return pos;
}

void updateMax(vector<int>& maxScores, string& tmp, int& categoryIndex, int audienceIndex) {
    int val = str2num(tmp);
    tmp.clear();
    if(audienceIndex == 0) {
        maxScores.push_back(val);
    }
    else if(val > maxScores[categoryIndex]) {
        maxScores[categoryIndex] = val;
    }
    ++categoryIndex;
}

void printMax(char* str, int maxlen) {
    vector<int> maxScores;
    int audienceIndex = 0;
    int categoryIndex = 0;
    string tmp;
    for(int i=0;i<maxlen;++i) {
        if((str[i] == '|') || (str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
                updateMax(maxScores, tmp, categoryIndex, audienceIndex);
                break;
            }
            ++audienceIndex;
            categoryIndex = 0;
            ++i;  // there's a space after '|' !!
        }
        else if(str[i] == ' ') {
            updateMax(maxScores, tmp, categoryIndex, audienceIndex);
        }
        else {
            tmp += str[i];
        }
    }
    if(maxScores.size() > 0) {
        printf("%d", maxScores[0]);
        for(int i=1;i<(int)maxScores.size();++i) {
            printf(" %d", maxScores[i]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: HighestScore <fileContainingTestVectors>\n");
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
        printMax(currentLine, MAX_LINE);
    }
    fclose(fp);
    return 0;
}
