//
// Challenge name: Black Card
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/222/
// Compile       : g++ -Wall -g -o BlackCard BlackCard.cpp
//

#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

int read(vector<string>& vec, FILE* fp) {
    int num = 0;
    char name[32];
    while(!feof(fp) && (fscanf(fp, "%s", name) == 1)) {
        if(name[0] == '|') {
            fscanf(fp, "%d", &num);
            break;
        }
        vec.push_back(name);
    }
    return num;
}

void winner(vector<string>& vec, int num) {
    while(vec.size() != 1) {
        int len = (int)vec.size();
        int residue;
        if(len >= num) {
            residue = num - 1;
        } else {
            residue = num % len;
            if(residue == 0) {
                residue = len - 1;
            } else {
                residue--;
            }
        }
        vec.erase(vec.begin()+residue);
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: BlackCard <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        vector<string> vec;
        int num = read(vec, fp);
        if(num <= 0) {
            continue;
        }
        winner(vec, num);
        printf("%s\n", vec[0].c_str());
    }
    fclose(fp);
    return 0;
}
