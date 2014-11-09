//
// Challenge name: Working Experience
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/139/
// Compile       : g++ -Wall -g -o WorkingExperience WorkingExperience.cpp
//

#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#define MAX_LINE 4096
using namespace std;

map<string,int> months;
void initMonths() {
    months["Jan"] = 0;
    months["Feb"] = 1;
    months["Mar"] = 2;
    months["Apr"] = 3;
    months["May"] = 4;
    months["Jun"] = 5;
    months["Jul"] = 6;
    months["Aug"] = 7;
    months["Sep"] = 8;
    months["Oct"] = 9;
    months["Nov"] = 10;
    months["Dec"] = 11;
}

int getMonth(const string& mon) {
    return months[mon];
}

int str2num(const string& s) {
    stringstream ss(s);
    int pos;
    ss >> pos;
    return pos;
}

int getMonthsFromStart(const string& month, const string& year) {
    int yearNum = str2num(year);
    int monthNum = getMonth(month);
    return ((yearNum * 12) + monthNum);
}

struct Range {
    int start, end;
    int duration() const {
        return ((end - start + 1));
    }
    // assumption: the input range is already sorted in ascending order of start dates!
    int overlapDuration(const Range& in) const {
        if(end >= in.start) {
            int final = (end <= in.end)? end : in.end;
            return (final - in.start + 1);
        }
        return 0;
    }
};

struct RangeSorter {
    bool operator()(const Range& a, const Range& b) {
        return (a.start <= b.start);
    }
};

struct WorkEx: public vector<Range> {
    int totalDuration;
    void getWorks(char* str, int max) {
        totalDuration = 0;
        string month, year;
        string* curr = &month;
        Range r;
        for(int i=0;i<max;i++) {
            if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
                r.end = getMonthsFromStart(month, year);
                push_back(r);
                totalDuration += r.duration();
                break;
            }
            if(str[i] == '-') {
                r.start = getMonthsFromStart(month, year);
                month.clear();
                year.clear();
                curr = &month;
                continue;
            }
            if(str[i] == ';') {
                r.end = getMonthsFromStart(month, year);
                push_back(r);
                totalDuration += r.duration();
                month.clear();
                year.clear();
                curr = &month;
                ++i;  // there's a space after ';'!
                continue;
            }
            if(str[i] == ' ') {
                curr = &year;
                continue;
            }
            (*curr) += str[i];
        }
        RangeSorter sorterObj;
        sort(begin(), end(), sorterObj);
    }
    int actualWorkEx() const {
        int overlap = 0;
        int num = (int)size();
        for(int i=0;i<num;++i) {
            for(int j=i+1;j<num;++j) {
                int ov = at(i).overlapDuration(at(j));
                if(ov == 0) {
                    break;
                }
                overlap += ov;
            }
        }
        return ((totalDuration - overlap) / 12);
    }
};

int main(int argc, char** argv) {
    initMonths();
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: WorkingExperience <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        char currentLine[MAX_LINE];
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        if(currentLine[0] == '\0') {
            continue;
        }
        WorkEx works;
        works.getWorks(currentLine, MAX_LINE);
        printf("%d\n", works.actualWorkEx());
    }
    fclose(fp);
    return 0;
}
