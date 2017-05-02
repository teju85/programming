//
// Challenge name: TIME TO EAT
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/214/
// Compile       : g++ -Wall -g -o TimeToEat TimeToEat.cpp
//

#include <stdio.h>
#include <vector>
using namespace std;

struct TimeStamp {
    char time[8];
    int secs;
    bool valid;

    TimeStamp(FILE* fp): time(), secs(0), valid(false) {
        for(int i=0;i<8;++i) {
            if(fscanf(fp, "%c", &(time[i])) != 1) {
                return;
            }
        }
        valid = true;
        secs = evalSecs();
    }

    TimeStamp(const TimeStamp& a): time(), secs(a.secs), valid(a.valid) {
        for(int i=0;i<8;++i) {
            time[i] = a.time[i];
        }
    }

    void print() const {
        printf("%c%c%c%c%c%c%c%c", time[0], time[1], time[2], time[3], time[4],
               time[5], time[6], time[7]);
    }

    void operator=(const TimeStamp& a) {
        for(int i=0;i<8;++i) {
            time[i] = a.time[i];
        }
        secs = a.secs;
        valid = a.valid;
    }

    int evalSecs() {
        int out = 0;
        out += ((time[0] - '0') * 36000);
        out += ((time[1] - '0') * 3600);
        out += ((time[3] - '0') * 600);
        out += ((time[4] - '0') * 60);
        out += ((time[6] - '0') * 10);
        out += ((time[7] - '0') * 1);
        return out;
    }

    friend bool operator<(TimeStamp& a, TimeStamp& b) {
        return (a.secs < b.secs);
    }
};

void swap(TimeStamp& a, TimeStamp& b) {
    TimeStamp tmp(a);
    a = b;
    b = tmp;
}

void read(vector<TimeStamp>& vec, FILE* fp) {
    while(!feof(fp)) {
        TimeStamp s(fp);
        vec.push_back(s);
        char c = '\n';
        fscanf(fp, "%c", &c);
        if(c == '\n') {
            return;
        }
    }
}

void sort(vector<TimeStamp>& vec) {
    int len = (int)vec.size();
    for(int i=1;i<len;++i) {
        for(int j=0;j<i;++j) {
            if(vec[j] < vec[i]) {
                swap(vec[j], vec[i]);
            }
        }
    }
}

void print(const vector<TimeStamp>& vec) {
    int len = (int)vec.size();
    for(int i=0;i<len;++i) {
        if(i != 0) {
            printf(" ");
        }
        vec[i].print();
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: TimeToEat <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        vector<TimeStamp> vec;
        read(vec, fp);
        if(vec.size() <= 0) {
            continue;
        }
        sort(vec);
        print(vec);
    }
    fclose(fp);
    return 0;
}
