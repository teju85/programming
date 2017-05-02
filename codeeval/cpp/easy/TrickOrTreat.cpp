//
// Challenge name: TRICK OR TREAT
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/220/
// Compile       : g++ -Wall -g -o TrickOrTreat TrickOrTreat.cpp
//

#include <stdio.h>
#include <string.h>

struct TrickOrTreat {
    int nVampis;
    int nZombis;
    int nWitchs;
    int nHouses;
    int isValid;

    TrickOrTreat(FILE* fp) {
        char name[32];
        int val;
        isValid = false;
        nVampis = nZombis = nWitchs = nHouses = 0;
        int numRead = 0;
        while(!feof(fp) && (numRead < 4)) {
            if(fscanf(fp, "%s%d", name, &val) != 2) {
                continue;
            }
            if(!strcmp(name, "Vampires:")) {
                nVampis = val;
                numRead++;
            } else if(!strcmp(name, "Zombies:")) {
                nZombis = val;
                numRead++;
            } else if(!strcmp(name, "Witches:")) {
                nWitchs = val;
                numRead++;
            } else if(!strcmp(name, "Houses:")) {
                nHouses = val;
                numRead++;
            }
        }
        isValid = (numRead == 4);
    }

    int perChild() const {
        int totalChocs = (3 * nVampis) + (4 * nZombis) + (5 * nWitchs);
        totalChocs *= nHouses;
        int nChildren = nVampis + nZombis + nWitchs;
        return (totalChocs / nChildren);
    }
};

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: TrickOrTreat <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        TrickOrTreat tt(fp);
        if(!tt.isValid) {
            continue;
        }
        printf("%d\n", tt.perChild());
    }
    fclose(fp);
    return 0;
}
