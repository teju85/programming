//
// Challenge name: Racing Chars
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/136/
// Compile       : g++ -Wall -g -o RacingChars RacingChars.cpp
//

#include <stdio.h>
#include <string>
#include <vector>

#define MAX_LINE 51

using namespace std;


class Section: public string {
public:
    Section(const char* sec): string(sec), entries() {
        updateEntry();
    }
    ~Section() {
    }
    int getEntryAt(int pos) const {
        return entries[pos];
    }
    int numEntries() const {
        return (int)entries.size();
    }
    void print(char c, int pos) const {
        string s(*this);
        s[pos] = c;
        printf("%s\n", s.c_str());
    }
private:
    void updateEntry() {
        int len = (int) size();
        // always guaranteed to look for checkpoints first then gates
        for(int i=0;i<len;++i) {
            if(isCheckpoint(i)) {
                entries.push_back(i);
            }
        }
        for(int i=0;i<len;++i) {
            if(isGate(i)) {
                entries.push_back(i);
            }
        }
    }
    bool isObstruction(int pos) const {
        return (at(pos) == '#');
    }
    bool isCheckpoint(int pos) const {
        return (at(pos) == 'C');
    }
    bool isGate(int pos) const {
        return (at(pos) == '_');
    }
    vector<int> entries;
};

class Track: public vector<Section*> {
public:
    Track(FILE* fp): vector<Section*>(), positions() {
        getTrack(fp);
    }
    ~Track() {
        for(iterator i=begin();i!=end();++i) {
            Section* s = *i;
            delete s;
        }
        clear();
    }
    void findPath() {
        for(const_iterator i=begin();i!=end();++i) {
            positions.push_back(0);
        }
        _findPath(0);
    }
    void printPath() const {
        int len = (int)size();
        int pe = -1;
        for(int i=0;i<len;++i) {
            Section* s = at(i);
            int se = positions[i];
            if(pe == -1) {
                pe = se;
            }
            if(se == pe) {
                s->print('|', se);
            }
            else if(se < pe) {
                s->print('/', se);
            }
            else {
                s->print('\\', se);
            }
            pe = se;
        }
    }
private:
    void getTrack(FILE* fp) {
        char currentLine[MAX_LINE];
        while(!feof(fp)) {
            currentLine[0] = '\0';
            fgets(currentLine, MAX_LINE, fp);
            if(currentLine[0] == '\0') {
                continue;
            }
            for(int i=0;i<MAX_LINE;++i) {
                if(currentLine[i] == '\n') {
                    currentLine[i] = '\0';
                    break;
                }
            }
            push_back(new Section(currentLine));
        }
    }
    bool _findPath(int from, int prev=-1) {
        if(from >= (int)size()) {
            return true;
        }
        Section* s = at(from);
        int num = s->numEntries();
        for(int i=0;i<num;++i) {
            int en = s->getEntryAt(i);
            int diff = (en > prev)? (en - prev) : (prev - en);
            if((prev != -1) && (diff > 1)) {
                continue;
            }
            positions[from] = en;
            if(_findPath(from+1, en)) {
                return true;
            }
        }
        return false;
    }
    vector<int> positions;
};

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: RacingChars <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    Track track(fp);
    track.findPath();
    track.printPath();
    fclose(fp);
    return 0;
}
