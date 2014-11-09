//
// Challenge name: Sequence Transformation
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/130/
// Compile       : g++ -Wall -g -o SequenceTransformation SequenceTransformation.cpp
//

#include <stdio.h>
#include <string>
#include <vector>
#include <set>
using namespace std;

#define MAX_CHARS 1024


class State {
public:
    State(): z(), o() {}
    ~State() {}
    void printState() const {
        printf("0=");
        printVector(z);
        printf(" 1=");
        printVector(o);
    }
    void addZeroState(int id) {
        z.push_back(id);
    }
    void addOneState(int id) {
        o.push_back(id);
    }
    void updateActives(set<int>& result, char c, int currId) const {
        if(c == '0') {
            updateActives(z, result, currId);
        }
        else if(c == '1') {
            updateActives(o, result, currId);
        }
    }

private:
    void updateActives(const vector<int>& vec, set<int>& result, int currId) const {
        if(vec.empty()) {
            result.insert(currId);
            return;
        }
        for(vector<int>::const_iterator itr=vec.begin();itr!=vec.end();++itr) {
            result.insert(*itr);
        }
    }
    void printVector(const vector<int>& vec) const {
        if(vec.empty()) {
            printf("-");
            return;
        }
        bool first = true;
        for(vector<int>::const_iterator itr=vec.begin();itr!=vec.end();++itr) {
            if(!first) {
                printf(",");
            }
            printf("%d", *itr);
            first = false;
        }
    }

    vector<int> z, o;
};

class NFA {
public:
    NFA(const string& seq): states() {
        states.push_back(new State);
        string::const_iterator itr = seq.begin();
        char prev = *itr;
        for(++itr;itr!=seq.end();++itr) {
            if(prev != *itr) {
                addState(prev);
            }
            prev = *itr;
        }
        addState(prev, true);
    }

    ~NFA() {
        for(vector<State*>::iterator itr=states.begin();itr!=states.end();++itr) {
            delete *itr;
        }
        states.clear();
    }

    void printStates() const {
        int id = 0;
        for(vector<State*>::const_iterator itr=states.begin();itr!=states.end();++itr,++id) {
            printf("State=%d: ", id);
            (*itr)->printState();
            printf("\n");
        }
    }

    bool doesMatch(const string& bin) const {
        set<int> active;
        active.insert(0);
        for(string::const_iterator itr=bin.begin();itr!=bin.end();++itr) {
            //printf("Before: "); printActives(active);
            active = findNextActive(active, *itr);
            //printf("Ater: "); printActives(active);
        }
        int finalId = (int) states.size() - 2;
        if(active.find(finalId) != active.end()) {
            return true;
        }
        return false;
    }

private:
    void printActives(const set<int>& active) const {
        bool first = true;
        for(set<int>::const_iterator itr=active.begin();itr!=active.end();++itr) {
            printf("%d", *itr);
            if(!first) {
                printf(" ");
            }
            first = false;
        }
        printf("\n");
    }

    set<int> findNextActive(const set<int>& active, char c) const {
        set<int> result;
        for(set<int>::const_iterator itr=active.begin();itr!=active.end();++itr) {
            const State* s = states[*itr];
            s->updateActives(result, c, *itr);
        }
        return result;
    }

    void addState(char c, bool last=false) {
        int id = (int) states.size();
        State* prev = states.back();
        states.push_back(new State);
        if(c == 'B') {
            prev->addOneState(id);
            State* one = states.back();
            one->addOneState(id);
            if(last) {
                one->addZeroState(id+1);
            }
        }
        else if(c == 'A') {
            prev->addZeroState(id);
            prev->addOneState(id);
            State* oneZero = states.back();
            oneZero->addZeroState(id);
            oneZero->addOneState(id);
        }
        else {
            printf("ERROR: bad char found! '%c'\n", c);
        }
        if(last) {
            states.push_back(new State);
        }
    }

    vector<State*> states;
};


bool canTransform(const string& bin, const string& seq) {
    NFA n(seq);
    //n.printStates();
    return n.doesMatch(bin);
}

int main(int argc, char** argv) {
    FILE* fp;
    char buff[MAX_CHARS];
    if(argc != 2) {
        printf("USAGE: SequenceTransformation <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        if(fscanf(fp, "%s", buff) <= 0) {
            continue;
        }
        string bin(buff);
        if(fscanf(fp, "%s", buff) <= 0) {
            continue;
        }
        string seq(buff);
        if(bin.empty() || seq.empty()) {
            continue;
        }
        printf("%s\n", canTransform(bin, seq)? "Yes" : "No");
    }
    fclose(fp);
    return 0;
}
