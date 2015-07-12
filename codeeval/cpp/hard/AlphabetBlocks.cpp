//
// Challenge name: Alphabet Blocks
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/201/
// Compile       : g++ -Wall -g -o AlphabetBlocks AlphabetBlocks.cpp
//

#include <stdio.h>
#include <string>
#include <vector>
#include <set>
using namespace std;

#define WORD_SIZE 32

struct Blocks {
    int nBlks;
    string str;
    vector<string> blks;
    vector<vector<int> > matches;

    bool read(FILE* fp) {
        if(fscanf(fp, "%d", &nBlks) != 1) {
            return false;
        }
        char words[WORD_SIZE];
        fscanf(fp, " | %s", words);
        str = words;
        fscanf(fp, " | %s", words);
        blks.push_back(words);
        for(int i=1;i<nBlks;++i) {
            fscanf(fp, "%s", words);
            blks.push_back(words);
        }
        generateMatches();
        return true;
    }

    bool canGenerate() {
        set<int> visited;
        return dfs(0, visited);
    }

private:
    bool dfs(int i, set<int>& visited) {
        if(i == (int)str.size()) {
            return true;
        }
        vector<int>& block = matches[i];
        for(vector<int>::iterator itr=block.begin();itr!=block.end();++itr) {
            if(visited.find(*itr) != visited.end()) {
                continue;
            }
            visited.insert(*itr);
            if(dfs(i+1, visited)) {
                return true;
            }
            visited.erase(*itr);
        }
        return false;
    }

    void generateMatches() {
        int len = (int)str.size();
        for(int j=0;j<len;++j) {
            vector<int> list;
            for(int i=0;i<nBlks;++i) {
                if(blks[i].find(str[j]) != string::npos) {
                    list.push_back(i);
                }
            }
            matches.push_back(list);
        }
    }
};

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: AlphabetBlocks <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        Blocks blk;
        if(!blk.read(fp)) {
            continue;
        }
        printf("%s\n", blk.canGenerate()? "True" : "False");
    }
    fclose(fp);
    return 0;
}
