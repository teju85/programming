//
// Challenge name: Suggest Groups
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/165/
// Compile       : g++ -Wall -g -o SuggestGroups SuggestGroups.cpp
//

#include <stdio.h>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;
#define MAX_LINE 4096

struct User {
    string name;
    vector<string> frnds;
    set<string> groups;
    bool alreadySubscribesTo(const string& g) const {
        return (groups.find(g) != groups.end());
    }
};

struct Graph {
    map<string, User> users;
    void suggestFor(const User& user) {
        map<string,int> counts;
        for(vector<string>::const_iterator i=user.frnds.begin();i!=user.frnds.end();++i) {
            const set<string>& grps = users[*i].groups;
            for(set<string>::const_iterator g=grps.begin();g!=grps.end();++g) {
                if(counts.find(*g) == counts.end()) {
                    counts[*g] = 1;
                }
                else {
                    counts[*g] += 1;
                }
            }
        }
        float thresh = ((float)user.frnds.size()) * 0.5f;
        vector<string> sugg;
        for(map<string,int>::const_iterator i=counts.begin();i!=counts.end();++i) {
            if((i->second >= thresh) && !user.alreadySubscribesTo(i->first)) {
                sugg.push_back(i->first);
            }
        }
        if(sugg.size() > 0) {
            printf("%s:", user.name.c_str());
            vector<string>::const_iterator i=sugg.begin();
            printf("%s", i->c_str());
            for(++i;i!=sugg.end();++i) {
                printf(",%s",  i->c_str());
            }
            printf("\n");
        }
    }
    void suggest() {
        for(map<string, User>::const_iterator i=users.begin();i!=users.end();++i) {
            suggestFor(i->second);
        }
    }
};

void updateUser(User& u, Graph& g, int numColons, string& s) {
    if(s.size() <= 0) {
        return;
    }
    if(numColons == 0) {
        u.name = s;
    }
    else if(numColons == 1) {
        u.frnds.push_back(s);
    }
    else {
        u.groups.insert(s);
    }
    s.clear();
}

void updateGraphFromLine(Graph& g, char* str, int max) {
    string s;
    User user;
    int numColons = 0;
    for(int i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            updateUser(user, g, numColons, s);
            break;
        }
        if(str[i] == ':') {
            updateUser(user, g, numColons, s);
            ++numColons;
            continue;
        }
        if(str[i] == ',') {
            updateUser(user, g, numColons, s);
            continue;
        }
        s += str[i];
    }
    g.users[user.name] = user;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: SuggestGroups <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    Graph g;
    while(!feof(fp)) {
        char currentLine[MAX_LINE];
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        if(currentLine[0] == '\0') {
            continue;
        }
        updateGraphFromLine(g, currentLine, MAX_LINE);
    }
    fclose(fp);
    g.suggest();
    return 0;
}
