//
// Challenge name: Locks
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/153/
// Compile       : g++ -Wall -g -o Locks Locks.cpp
//

#include <stdio.h>

/*
// 1 = Locked, 0 = Unlocked
// only 2      1 1 1 1
// only 3      0 1 1 0
// both        1 0 1 0
// none        0 0 0 0

const bool LOCK_TABLE[][6] = {
    {1, 0, 1, 0, 1, 0},
    {0, 0, 1, 1, 1, 0},
    {1, 0, 1, 1, 1, 0},
    {0, 0, 1, 0, 1, 0},
};

bool isLockedAfter(int doorPosition, int mTimes) {
    --mTimes;  // count starts from '0'
    // initial is unlocked
    if(mTimes < 0) {
        return false;
    }
    int divBy6 = doorPosition % 6;
    int divBy4 = mTimes % 4;
    return LOCK_TABLE[divBy4][divBy6];
}

int countNumUnlocked(int numDoors, int mTimes) {
    int num = 0;
    int m1 = mTimes - 1;
    bool lastDoorLocked = false;
    for(int i=0;i<numDoors;++i) {
        if(isLockedAfter(i, m1)) {
            lastDoorLocked = true;
        }
        else {
            ++num;
            lastDoorLocked = false;
        }
    }
    // last iteration
    if(lastDoorLocked) {
        ++num;
    }
    else {
        --num;
    }
    return num;
}
*/

int countNumUnlocked(int numDoors, int mTimes) {
    bool* doors = new bool[numDoors];
    for(int i=0;i<numDoors;++i) {
        doors[i] = false;
    }
    for(int i=1;i<mTimes;++i) {
        for(int j=0;j<numDoors;j+=2) {
            doors[j] = true;
        }
        ++i;
        if(i < mTimes) {
            for(int j=0;j<numDoors;j+=3) {
                doors[j] = !doors[j];
            }
        }
    }
    doors[numDoors-1] = !doors[numDoors-1];
    delete [] doors;
    int count = 0;
    for(int i=0;i<numDoors;++i) {
        if(!doors[i]) {
            ++count;
        }
    }
    return count;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: Locks <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int numDoors, numTimes;
        if(fscanf(fp, "%d%d", &numDoors, &numTimes) != 2) {
            continue;
        }
        printf("%d\n", countNumUnlocked(numDoors, numTimes));
    }
    fclose(fp);
    return 0;
}
