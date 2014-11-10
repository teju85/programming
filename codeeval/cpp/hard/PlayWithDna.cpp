//
// Challenge name: Play With Dna
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/126/
// Compile       : g++ -Wall -g -o PlayWithDna PlayWithDna.cpp
//

#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX_LINE 1024

int str2num(const string& s) {
    stringstream ss(s);
    int pos;
    ss >> pos;
    return pos;
}

int mini(int a, int b, int c) {
    return ((a < b)? ((a < c)? a : c) : ((b < c)? b : c));
}

int editDistance(const char* s1, const char* s2, int len, int** edit) {
    edit[0][0] = 0;
    for(int i=1;i<=len;++i) {
        edit[i][0] = i;
        edit[0][i] = i;
    }
    for(int i=1;i<=len;++i) {
        for(int j=1;j<=len;++j) {
            if(s1[i-1] == s2[j-1]) {
                edit[i][j] = edit[i-1][j-1];
            }
            else {
                edit[i][j] = mini(edit[i-1][j], edit[i-1][j-1], edit[i][j-1]) + 1;
            }
        }
    }
    return edit[len][len];
}

struct Match {
    int mismatch;
    string str;
};

struct Compare {
    bool operator()(const Match& m1, const Match& m2) const {
        if(m1.mismatch == m2.mismatch) {
            return (m1.str < m2.str);
        }
        return (m1.mismatch < m2.mismatch);
    }
};

void printOccurences(const char* kmer, int kmerLen,
                     const char* dna, int dnaLen,
                     int numMismatches, int** edit) {
    vector<Match> occ;
    int limit = dnaLen - kmerLen + 1;
    for(int i=0;i<limit;++i) {
        int mis = editDistance(kmer, dna+i, kmerLen, edit);
        if(mis <= numMismatches) {
            Match m = {mis, string(dna+i, kmerLen)};
            occ.push_back(m);
        }
    }
    if(occ.size() > 0) {
        sort(occ.begin(), occ.end(), Compare());
        vector<Match>::const_iterator i = occ.begin();
        printf("%s", i->str.c_str());
        for(++i;i!=occ.end();++i) {
            printf(" %s", i->str.c_str());
        }
        printf("\n");
    }
    else {
        printf("No match\n");
    }
}

void findOccurences(char* str, int max) {
    string s;
    int numMismatches = 0;
    int numSpaces = 0;
    int kmerStart = 0;
    int kmerLen = 0;
    int dnaStart = 0;
    int dnaLen = 0;
    for(int i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            dnaLen = i - dnaStart;
            break;
        }
        if(str[i] == ' ') {
            if(numSpaces == 0) {
                kmerLen = i;
            }
            else if(numSpaces == 1) {
                dnaStart = i + 1;
                numMismatches = str2num(s);
            }
            ++numSpaces;
            continue;
        }
        if(numSpaces == 1) {
            s += str[i];
        }
    }
    int** edit = new int*[kmerLen+1];
    for(int i=0;i<=kmerLen;++i) {
        edit[i] = new int[kmerLen+1];
    }
    printOccurences(str+kmerStart, kmerLen, str+dnaStart, dnaLen, numMismatches, edit);
    for(int i=0;i<=kmerLen;++i) {
        delete [] edit[i];
    }
    delete [] edit;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: PlayWithDna <fileContainingTestVectors>\n");
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
        findOccurences(currentLine, MAX_LINE);
    }
    fclose(fp);
    return 0;
}
