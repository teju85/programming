//
// Challenge name: Split The Number
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/131/
// Compile       : g++ -Wall -g -o SplitTheNumber SplitTheNumber.cpp
//

#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

#define MAX_LINE 1024
#define NUM_DIGITS 16

#define INT long long int

bool isalpha(char c) {
    return ((c >= 'a') && (c <= 'z'));
}

bool isdigit(char c) {
    return ((c >= '0') && (c <= '9'));
}

INT str2num(const string& s) {
    stringstream ss(s);
    INT pos;
    ss >> pos;
    return pos;
}

INT add(char* nums, int numDigs, int splitPos) {
    string s1(nums, splitPos);
    string s2(nums+splitPos, numDigs-splitPos);
    return (str2num(s1) + str2num(s2));
}

INT sub(char* nums, int numDigs, int splitPos) {
    string s1(nums, splitPos);
    string s2(nums+splitPos, numDigs-splitPos);
    return (str2num(s1) - str2num(s2));
}

void split(char* str, int max) {
    char nums[NUM_DIGITS];
    int numDigs = 0;
    int splitPos = 0;
    for(int i=0;i<max;i++) {
        char c = str[i];
        if((c == '\n') || (c == '\r') || (c == '\0')) {
            return;
        }
        if(isdigit(c)) {
            nums[numDigs] = c;
            ++numDigs;
        }
        else if(isalpha(c)) {
            ++splitPos;
        }
        else if(c == '+') {
            printf("%lld\n", add(nums, numDigs, splitPos));
            return;
        }
        else if(c == '-') {
            printf("%lld\n", sub(nums, numDigs, splitPos));
            return;
        }
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: SplitTheNumber <fileContainingTestVectors>\n");
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
        split(currentLine, MAX_LINE);
    }
    fclose(fp);
    return 0;
}
