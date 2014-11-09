//
// Challenge name: Flavius Josephus
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/75/
// Compile       : g++ -Wall -g -o flaviusJosephus flaviusJosephus.cpp
//

#include <stdio.h>

int numSurvivors(bool* survivors, int num) {
    int sum = 0;
    for(int i=0;i<num;++i) {
        if(survivors[i]) {
            ++sum;
        }
    }
    return sum;
}

void findNextKilled(bool* survivors, int num, int count, int& toBeKilled) {
    int i = 0;
    while(i < count) {
        ++toBeKilled;
        if(toBeKilled >= num) {
            toBeKilled = 0;
        }
        if(survivors[toBeKilled]) {
            ++i;
        }
    }
}

void printKillOrder(int num, int count) {
    bool* survivors = new bool[num];
    for(int i=0;i<num;++i) {
        survivors[i] = true;
    }
    int toBeKilled = -1;
    while(numSurvivors(survivors, num) > 0) {
        findNextKilled(survivors, num, count, toBeKilled);
        survivors[toBeKilled] = false;
        printf("%d ", toBeKilled);
    }
    // last survivor
    for(int i=0;i<count;++i) {
        if(survivors[i]) {
            printf("%d", i);
            return;
        }
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: flaviusJosephus <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int num, count;
        count = 0;
        fscanf(fp, "%d,%d", &num, &count);
        if(count <= 0) {
            continue;
        }
        printKillOrder(num, count);
        printf("\n");
    }
    fclose(fp);
    return 0;
}
