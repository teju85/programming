//
// Challenge name: Data Recovery
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/140/
// Compile       : g++ -Wall -g -o DataRecovery DataRecovery.cpp
//

#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int str2num(const string& s) {
    stringstream ss(s);
    int pos;
    ss >> pos;
    return pos;
}

void getInput(FILE* fp, vector<string>& words, vector<int>& positions) {
    char c;
    string s;
    bool onWords = true;
    while(!feof(fp)) {
        c = fgetc(fp);
        if(c == '\n') {
            positions.push_back(str2num(s));
            return;
        }
        if(c == ' ') {
            if(onWords) {
                words.push_back(s);
            }
            else {
                positions.push_back(str2num(s));
            }
            s.clear();
            continue;
        }
        if(c == ';') {
            onWords = false;
            words.push_back(s);
            s.clear();
            continue;
        }
        s += c;
    }
    positions.push_back(str2num(s));
}

void mapMissingInput(vector<string>& words, vector<int>& positions) {
    if(words.size() == positions.size()) {
        return;
    }
    if(words.size() != (positions.size() + 1)) {
        return;
    }
    int n = (int)words.size();
    int total = (n * (n + 1)) / 2;
    int sum = 0;
    for(vector<int>::iterator i=positions.begin();i!=positions.end();++i) {
        sum += *i;
    }
    positions.push_back(total - sum);
}

void printWords(vector<string>& words, vector<int>& pos) {
    int n = (int)words.size();
    bool first = true;
    for(int i=1;i<=n;++i) {
        int loc = 0;
        for(vector<int>::iterator itr=pos.begin();itr!=pos.end();++itr,++loc) {
            if(*itr == i) {
                break;
            }
        }
        if(first) {
            printf("%s", words[loc].c_str());
            first = false;
        }
        else {
            printf(" %s", words[loc].c_str());
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: DataRecovery <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        vector<string> words;
        vector<int> pos;
        getInput(fp, words, pos);
        if(words.empty() || pos.empty()) {
            continue;
        }
        mapMissingInput(words, pos);
        printWords(words, pos);
    }
    fclose(fp);
    return 0;
}
