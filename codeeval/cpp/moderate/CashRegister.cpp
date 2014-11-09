//
// Challenge name: Cash Register
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/54/
// Compile       : g++ -Wall -g -o CashRegister CashRegister.cpp
//

#include <stdio.h>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int,string>  Change;
typedef vector<Change>    ChangeList;


struct Cash {
public:
    int i;
    int f;

    Cash(): i(0),f(0) {}
    Cash(int _i, int _f=0): i(_i), f(_f) {}
    Cash(const Cash& a): i(a.i), f(a.f) {}
    ~Cash() {}

    const Cash& operator=(const Cash& a) {
        i = a.i;
        f = a.f;
        return *this;
    }

    bool operator==(const Cash& a) {
        return ((i == a.i) && (f == a.f));
    }

    bool operator<(const Cash& a) {
        if(i < a.i)       return true;
        else if(i > a.i)  return false;
        else if(f < a.f)  return true;
        else              return false;
    }

    const Cash& operator-=(const Cash& a) {
        if(f < a.f) {
            --i;
            f = (100 + f - a.f);
        }
        i -= a.i;
        return *this;
    }

    friend Cash operator-(const Cash& a, const Cash& b) {
        Cash c = a;
        c -= b;
        return c;
    }

    char read(FILE* fp) {
        i = f = 0;
        fscanf(fp, "%d", &i);
        char c;
        fscanf(fp, "%c", &c);
        if(c == '.') {
            fscanf(fp, "%d", &f);
        }
        return c;
    }

    void print() const {
        printf("%d.%02d", i, f);
    }

    bool isZero() const {
        return ((i == 0) && (f == 0));
    }
};


void readInput(FILE* fp, Cash& pp, Cash& ch) {
    char c = pp.read(fp);
    if(c != ';') {
        fscanf(fp, "%c", &c);  // This has to be ';'!!
    }
    ch.read(fp);
}

bool alphaSortFunc(const string& a, const string& b) {
    return (a.compare(b) < 0);
}

void printChange(const string& s) {
    printf(",%s", s.c_str());
}

void evalChange(Cash& c, ChangeList& ci, ChangeList& cf) {
    vector<string> change;
    for(ChangeList::iterator itr=ci.begin();itr!=ci.end();++itr) {
        int val = itr->first;
        if(c.i >= val) {
            int n = c.i / val;
            c.i %= val;
            for(;n>0;--n) {
                change.push_back(itr->second);
            }
        }
    }
    for(ChangeList::iterator itr=cf.begin();itr!=cf.end();++itr) {
        int val = itr->first;
        if(c.f >= val) {
            int n = c.f / val;
            c.f %= val;
            for(;n>0;--n) {
                change.push_back(itr->second);
            }
        }
    }
    sort(change.begin(), change.end(), alphaSortFunc);
    printf("%s", change[0].c_str());
    for_each(change.begin()+1, change.end(), printChange);
    printf("\n");
}


int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: SpiralPrinting <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    ChangeList cli;
    cli.push_back(make_pair(100, "ONE HUNDRED"));
    cli.push_back(make_pair(50, "FIFTY"));
    cli.push_back(make_pair(20, "TWENTY"));
    cli.push_back(make_pair(10, "TEN"));
    cli.push_back(make_pair(5, "FIVE"));
    cli.push_back(make_pair(2, "TWO"));
    cli.push_back(make_pair(1, "ONE"));
    ChangeList clf;
    clf.push_back(make_pair(50, "HALF DOLLAR"));
    clf.push_back(make_pair(25, "QUARTER"));
    clf.push_back(make_pair(10, "DIME"));
    clf.push_back(make_pair(5, "NICKEL"));
    clf.push_back(make_pair(1, "PENNY"));
    while(!feof(fp)) {
        Cash pp, ch;
        readInput(fp, pp, ch);
        if(pp.isZero() && ch.isZero()) {
            continue;
        }
        if(ch < pp) {
            printf("ERROR\n");
            continue;
        }
        if(ch == pp) {
            printf("ZERO\n");
            continue;
        }
        Cash diff = ch - pp;
        evalChange(diff, cli, clf);
    }
    fclose(fp);
    return 0;
}
