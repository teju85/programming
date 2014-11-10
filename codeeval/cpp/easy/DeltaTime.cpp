//
// Challenge name: Delta Time
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/166/
// Compile       : g++ -Wall -g -o DeltaTime DeltaTime.cpp
//

#include <stdio.h>
#define MAX_LINE 1024

int stringLen(char* str, int max) {
    int i;
    for(i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            str[i] = '\0';
            return i;
        }
    }
    return max;
}

int char2digit(char c) {
    return (int)(c - '0');
}

class Time {
public:
    Time(char* str): hour(0), min(0), sec(0) {
        hour = (char2digit(str[0]) * 10) + char2digit(str[1]);
        min = (char2digit(str[3]) * 10) + char2digit(str[4]);
        sec = (char2digit(str[6]) * 10) + char2digit(str[7]);
    }
    Time(int seconds): hour(0), min(0), sec(0) {
        hour = seconds / 3600;
        seconds %= 3600;
        min = seconds / 60;
        sec = seconds % 60;
    }
    Time(const Time& t): hour(t.hour), min(t.min), sec(t.sec) {
    }
    ~Time() {
    }
    Time delta(const Time& b) const {
        int del = toSeconds() - b.toSeconds();
        if(del < 0) {
            del = -del;
        }
        return Time(del);
    }
    int toSeconds() const {
        int out = (hour * 3600) + (min * 60) + sec;
        return out;
    }
    void print() const {
        printf("%02d:%02d:%02d\n", hour, min, sec);
    }
private:
    int hour;
    int min;
    int sec;
};

void deltaTime(char* str, int len) {
    int space;
    for(space=0;space<len;++space) {
        if(str[space] == ' ') {
            break;
        }
    }
    Time t1(str);
    Time t2(str+space+1);
    t1.delta(t2).print();
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: DeltaTime <fileContainingTestVectors>\n");
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
        int len = stringLen(currentLine, MAX_LINE);
        if(len <= 0) {
            continue;
        }
        deltaTime(currentLine, len);
    }
    fclose(fp);
    return 0;
}
