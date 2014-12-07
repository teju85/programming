//
// Challenge name: Without Repetitions
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/173/
// Compile       : g++ -Wall -g -o WithoutRepetitions WithoutRepetitions.cpp
//

#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

void noRepeats(const string& ss) {
    char prev = '\0';
    int len = (int)ss.size();
    for(int i=0;i<len;++i) {
        if(prev != ss[i]) {
            printf("%c", ss[i]);
            prev = ss[i];
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("USAGE: WithoutRepetitions <fileContainingTestVectors>\n");
        return 1;
    }
    ifstream ifs;
    ifs.open(argv[1], ifstream::in);
    if(!ifs.is_open()) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(ifs.good()) {
        string ss;
        getline(ifs, ss);
        if(ss.size() <= 0) {
            continue;
        }
        noRepeats(ss);
    }
    ifs.close();
    return 0;
}
