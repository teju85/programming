//
// Challenge name: Sequence Transformation
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/130/
// Compile       : g++ -Wall -g -o SequenceTransformation SequenceTransformation.cpp
//

#include <stdio.h>
#include <string>
#include <vector>
#include <set>
using namespace std;

#define MAX_CHARS 1024




bool isCompatible(const string& bin, const string& seq, int binPos, int seqPos) {
    if(binPos >= (int)bin.size()) {
        return false;
    }
    if(seqPos >= (int)seq.size()) {
        return false;
    }
    if((bin[binPos] == '0') && (seq[seqPos] == 'B')) {
        return false;
    }
    return true;
}

bool hasToggleNext(const string& s, int pos) {
    int len = (int)s.size();
    if(pos >= len-1) {
        return false;
    }
    return (s[pos] != s[pos+1]);
}

bool _can(const string& bin, const string& seq, int binPos, int seqPos) {
    int binLen = (int)bin.size();
    int seqLen = (int)seq.size();
    if(!isCompatible(bin, seq, binPos, seqPos)) {
        return false;
    }
    if((binPos == binLen-1) && (seqPos == seqLen-1)) {
        return true;
    }
    if(hasToggleNext(seq, seqPos)) {
        if(_can(bin, seq, binPos+1, seqPos+1)) {
            return true;
        }
    }
    else {
        if(_can(bin, seq, binPos, seqPos+1)) {
            return true;
        }
        if(_can(bin, seq, binPos+1, seqPos+1)) {
            return true;
        }
    }
    return false;
}

bool canTransform(const string& bin, const string& seq) {
    if(bin.size() > seq.size()) {
        return false;
    }
    return _can(bin, seq, 0, 0);
}

int main(int argc, char** argv) {
    FILE* fp;
    char buff[MAX_CHARS];
    if(argc != 2) {
        printf("USAGE: SequenceTransformation <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        if(fscanf(fp, "%s", buff) <= 0) {
            continue;
        }
        string bin(buff);
        if(fscanf(fp, "%s", buff) <= 0) {
            continue;
        }
        string seq(buff);
        if(bin.empty() || seq.empty()) {
            continue;
        }
        printf("%s\n", canTransform(bin, seq)? "Yes" : "No");
    }
    fclose(fp);
    return 0;
}
