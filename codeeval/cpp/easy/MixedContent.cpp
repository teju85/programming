//
// Challenge name: Mixed Content
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/115/
// Compile       : g++ -Wall -g -o MixedContent MixedContent.cpp
//

#include <stdio.h>
#include <string>
#include <vector>
#define MAX_LINE 1024
using namespace std;

bool isdigit(char c) {
    return ((c >= '0') && (c <= '9'));
}

void separateWords(char* str, int max, vector<string>& words, vector<string>& digits) {
    bool containsLetters = false;
    string temp;
    for(int i=0;i<max;i++) {
        if((str[i] == ',') || (str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            if(containsLetters) {
                words.push_back(temp);
            }
            else {
                digits.push_back(temp);
            }
            temp = "";
            if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
                break;
            }
            containsLetters = false;
            continue;
        }
        if(!isdigit(str[i])) {
            containsLetters = true;
        }
        temp += str[i];
    }
}

void printSeparateWords(const vector<string>& words, const vector<string>& digits) {
    bool first = true;
    for(vector<string>::const_iterator itr=words.begin();itr!=words.end();++itr) {
        if(!first) {
            printf(",%s", itr->c_str());
        }
        else {
            printf("%s", itr->c_str());
            first = false;
        }
    }
    if((words.size() > 0) && (digits.size() > 0)) {
        printf("|");
    }
    first = true;
    for(vector<string>::const_iterator itr=digits.begin();itr!=digits.end();++itr) {
        if(!first) {
            printf(",%s", itr->c_str());
        }
        else {
            printf("%s", itr->c_str());
            first = false;
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: MixedContent <fileContainingTestVectors>\n");
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
        vector<string> words, digits;
        separateWords(currentLine, MAX_LINE, words, digits);
        printSeparateWords(words, digits);
    }
    fclose(fp);
    return 0;
}
