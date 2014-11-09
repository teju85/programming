//
// Challenge name: Compressed Sequence
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/128/
// Compile       : g++ -Wall -g -o CompressedSequence CompressedSequence.cpp
//

#include <stdio.h>
#include <vector>
using namespace std;

void compress(FILE* fp) {
    vector<int> seqs;
    int prevNum = -1;
    int count = 0;
    while(!feof(fp)) {
        int num = -1;
        if(fscanf(fp, "%d", &num) != 1) {
            break;
        }
        if(prevNum == num) {
            ++count;
        }
        else if(count != 0) {
            seqs.push_back(count);
            seqs.push_back(prevNum);
            count = 1;
            prevNum = num;
        }
        else {
            count = 1;
            prevNum = num;
        }
        char c = getc(fp);
        ungetc(c, fp);
        if(c == '\n') {
            seqs.push_back(count);
            seqs.push_back(prevNum);
            break;
        }
        if(feof(fp)) {
            seqs.push_back(count);
            seqs.push_back(prevNum);
            break;
        }
    }
    if(seqs.size() <= 0) {
        return;
    }
    for(size_t i=0;i<seqs.size();i+=2) {
        if(i != 0) {
            printf(" ");
        }
        printf("%d %d", seqs[i], seqs[i+1]);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: CompressedSequence <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        compress(fp);
    }
    fclose(fp);
    return 0;
}
