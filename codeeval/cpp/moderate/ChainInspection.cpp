//
// Challenge name: Chain Inspection
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/119/
// Compile       : g++ -Wall -g -o ChainInspection ChainInspection.cpp
//

#include <stdio.h>
#include <string>
#include <map>
#include <set>
using namespace std;

#define MAX_LINE 32768

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

void populateMap(char* str, int len, map<string,string>& index, set<string>& elements) {
    string key = "";
    string curr = "";
    for(int i=0;i<len;++i) {
        if(str[i] == '-') {
            key = curr;
            curr = "";
            continue;
        }
        if(str[i] == ';') {
            index[key] = curr;
            elements.insert(curr);
            elements.insert(key);
            curr = "";
            key = "";
            continue;
        }
        curr += str[i];
    }
    if((curr != "") && (key != "")) {
        index[key] = curr;
        elements.insert(curr);
        elements.insert(key);
    }
}

bool isGood(char* str, int len) {
    map<string,string> index;
    set<string> elements;
    populateMap(str, len, index, elements);
    string curr = "BEGIN";
    while(true) {
        if(elements.find(curr) == elements.end()) {
            return false;
        }
        elements.erase(curr);
        if(curr == "END") {
            break;
        }
        curr = index[curr];
    }
    return (0 == elements.size());
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: ChainInspection <fileContainingTestVectors>\n");
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
        printf("%s\n", isGood(currentLine, len)? "GOOD" : "BAD");
    }
    fclose(fp);
    return 0;
}
