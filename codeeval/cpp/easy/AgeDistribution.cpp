//
// Challenge name: Age Distribution
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/152/
// Compile       : g++ -Wall -g -o AgeDistribution AgeDistribution.cpp
//

#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

void initializeAgeVector(vector<string>& arr) {
    arr.push_back("Still in Mama's arms");
    arr.push_back("Preschool Maniac");
    arr.push_back("Elementary school");
    arr.push_back("Middle school");
    arr.push_back("High school");
    arr.push_back("College");
    arr.push_back("Working for the man");
    arr.push_back("The Golden Years");
    arr.push_back("This program is for humans");
}

int giveArrayIndex(int age) {
    if(age >= 0  &&  age <= 2) {
        return 0;
    }
    if(age >= 3  &&  age <= 4) {
        return 1;
    }
    if(age >= 5  &&  age <= 11) {
        return 2;
    }
    if(age >= 12  &&  age <= 14) {
        return 3;
    }
    if(age >= 15  &&  age <= 18) {
        return 4;
    }
    if(age >= 19  &&  age <= 22) {
        return 5;
    }
    if(age >= 23  &&  age <= 65) {
        return 6;
    }
    if(age >= 66  &&  age <= 100) {
        return 7;
    }
    return 8;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: AgeDistribution <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    vector<string> ageDist;
    initializeAgeVector(ageDist);
    while(!feof(fp)) {
        int age = 0;
        if(fscanf(fp, "%d", &age) <= 0) {
            continue;
        }
        printf("%s\n", ageDist[giveArrayIndex(age)].c_str());
    }
    fclose(fp);
    return 0;
}
