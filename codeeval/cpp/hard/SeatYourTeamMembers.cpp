//
// Challenge name: Seat your team members
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/118/
// Compile       : g++ -Wall -g -o SeatYourTeamMembers SeatYourTeamMembers.cpp
//

#include <stdio.h>
#include <vector>
using namespace std;

struct Preference {
    int id;
    vector<int> prefs;
    bool populate(FILE* fp, bool& last) {
        last = false;
        if(fscanf(fp, "%d:[", &id) != 1) {
            return false;
        }
        int p;
        while(true) {
            if(fscanf(fp, "%d, ", &p) != 1) {
                break;
            }
            prefs.push_back(p);
        }
        fscanf(fp, "]");
        char c = '\0';
        fscanf(fp, "%c", &c);
        if(c == '\n') {
            last = true;
            return true;
        }
        fscanf(fp, " ");
        return true;
    }
};

struct PreferenceList {
    vector<Preference> prefs;
    int numSlots;
    bool* occupancy;
    PreferenceList(): prefs(), numSlots(0), occupancy(NULL) {
    }
    ~PreferenceList() {
        if(occupancy != NULL) {
            delete [] occupancy;
        }
    }
    bool populate(FILE* fp) {
        if(fscanf(fp, "%d; ", &numSlots) != 1) {
            return false;
        }
        occupancy = new bool[numSlots];
        for(int i=0;i<numSlots;++i) {
            occupancy[i] = false;
        }
        while(true) {
            Preference pref;
            bool last;
            if(!pref.populate(fp, last)) {
                break;
            }
            prefs.push_back(pref);
            if(last) {
                break;
            }
        }
        return true;
    }
    bool canBeSeated(int pos=0) {
        if(pos >= (int)prefs.size()) {
            return true;
        }
        const Preference p = prefs[pos];
        for(vector<int>::const_iterator itr=p.prefs.begin();itr!=p.prefs.end();++itr) {
            int seat = *itr - 1;
            if(occupancy[seat]) {
                continue;
            }
            occupancy[seat] = true;
            if(canBeSeated(pos+1)) {
                return true;
            }
            occupancy[seat] = false;
        }
        return false;
    }
private:
    bool allOccupied() const {
        for(int i=0;i<numSlots;++i) {
            if(!occupancy[i]) {
                return false;
            }
        }
        return true;
    }
};

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: SeatYourTeamMembers <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        PreferenceList list;
        if(!list.populate(fp)) {
            break;
        }
        printf("%s\n", list.canBeSeated()? "Yes" : "No");
    }
    fclose(fp);
    return 0;
}
