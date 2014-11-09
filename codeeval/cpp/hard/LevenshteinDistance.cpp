//
// Challenge name: Levenshtein Distance
// Difficulty    : hard
// Link          : http://codeeval.com/open_challenges/58/
// Compile       : g++ -Wall -g -o LevenshteinDistance LevenshteinDistance.cpp
//

#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

#define MAX_LINE 512
#define MIN(x, y, z)   ((x < y)? ((x < z)? x : z) : ((y < z)? y : z))
#define THRESH 1
#define MAX_WORDS 64

int lev[MAX_WORDS][MAX_WORDS];

vector<string> words;
vector<string> searchSpace;
set<string> friends;
vector<string> friendsList;

int levenshteinDistance(const string& s1, const string& s2) {
    const char* a = s1.c_str();
    int alen = (int) s1.size();
    const char* b = s2.c_str();
    int blen = (int) s2.size();
    for(int i=0;i<=alen;++i) {
        lev[i][0] = i;
    }
    for(int j=0;j<=blen;++j) {
        lev[0][j] = j;
    }
    for(int i=1;i<=alen;++i) {
        for(int j=1;j<=blen;++j) {
            int x = lev[i-1][j] + 1;
            int y = lev[i][j-1] + 1;
            int z = lev[i-1][j-1] + (a[i-1] != b[j-1]);
            lev[i][j] = MIN(x, y, z);
        }
    }
    return lev[alen][blen];
}

bool isFriend(const string& a, const string& b) {
    int diff = (int) ((a.size() < b.size())? b.size() - a.size()  :  a.size() - b.size());
    if(diff > THRESH) {
        return false;
    }
    if(a == b) {
        return false;
    }
    return (levenshteinDistance(a, b) == THRESH);
}

void clear() {
    friends.clear();
    friendsList.clear();
}

void work(const string& s) {
    for(vector<string>::const_iterator itr=searchSpace.begin();itr!=searchSpace.end();++itr) {
        if((friends.find(*itr) == friends.end()) && isFriend(s, *itr)) {
            friends.insert(*itr);
            friendsList.push_back(*itr);
        }
    }
}

string pop_front(vector<string>& vec) {
    swap(vec[0], vec.back());
    string out = vec.back();
    vec.pop_back();
    return out;
}

void workOnCurrentList() {
    while(friendsList.size() > 0) {
        string s = pop_front(friendsList);
        work(s);
    }
}

int main(int argc, char** argv) {
    bool inputEnded = false;
    if(argc != 2) {
        printf("USAGE: LevenshteinDistance <fileContainingTestVectors>\n");
        return 1;
    }
    ifstream ifs(argv[1]);
    if(!ifs.is_open()) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!ifs.eof()) {
        string s;
        getline(ifs, s);
        if(s == "END OF INPUT") {
            inputEnded = true;
            continue;
        }
        if(!inputEnded) {
            words.push_back(s);
        }
        else {
            searchSpace.push_back(s);
        }
    }
    ifs.close();
    for(vector<string>::const_iterator itr=words.begin();itr!=words.end();++itr) {
        clear();
        friends.insert(*itr);
        friendsList.push_back(*itr);
        workOnCurrentList();
        printf("%d\n", (int)friends.size());
    }
    return 0;
}
