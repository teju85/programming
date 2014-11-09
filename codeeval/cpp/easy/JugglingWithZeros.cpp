//
// Challenge name: Juggling With Zeros
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/149/
// Compile       : g++ -Wall -g -o JugglingWithZeros JugglingWithZeros.cpp
//

#include <stdio.h>
#include <string>
#define MAX_LINE 1024

#define INT unsigned long long int


using namespace std;


bool isZero(const string& s) {
    return (s == "0");
}

INT updateVal(INT val, const string& ss, int type) {
    int num = (int) ss.size();
    val <<= num;
    if(type == 1) {
        INT tmp = (1 << num) - 1;
        val |= tmp;
    }
    return val;
}

INT findVal(char* str, int max) {
    INT val = 0;
    int type = -1;
    string ss;
    ss.clear();
    for(int i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            val = updateVal(val, ss, type);
            break;
        }
        if(str[i] == ' ') {
            if(type >= 0) {
                val = updateVal(val, ss, type);
                type = -1;
            }
            else {
                type = isZero(ss)? 0 : 1;
            }
            ss.clear();
            continue;
        }
        ss += str[i];
    }
    return val;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: JugglingWithZeros <fileContainingTestVectors>\n");
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
        printf("%llu\n", findVal(currentLine, MAX_LINE));
    }
    fclose(fp);
    return 0;
}
