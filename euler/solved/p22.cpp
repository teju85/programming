//
// Challenge name: Problem 22
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=22
// Compile       : g++ -Wall -g -o p22 p22.cpp
// Run           : ./p22 p22.txt
//

#include <stdio.h>
#include <list>
#include <string>
#include "include/characters.h"
using namespace std;

#define INT unsigned int
#define CHARS 32
char name[CHARS];


int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: p22 <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open '%s' for reading!\n", argv[1]);
        return 2;
    }
    list<string> names;
    while(!feof(fp)) {
        fscanf(fp, "%s", name);
        if(!feof(fp)) {
            string str = name;
            names.push_back(str);
        }
    }
    fclose(fp);
    names.sort();
    INT i = 1;
    INT total = 0;
    for(list<string>::iterator it=names.begin();it!=names.end();++it,++i) {
        INT sum = (INT) sum_of_alphabets(it->c_str(), (int)it->size());
        total += (sum * i);
    }
    printf("%d\n", total);
    return 0;
}
