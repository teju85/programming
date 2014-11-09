//
// Challenge name: Road Trip
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/124/
// Compile       : g++ -Wall -g -o RoadTrip RoadTrip.cpp
//

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;
#define MAX_LINE 16384

void getCities(char* str, int max, vector<int>& dist) {
    string num;
    bool number = false;
    for(int i=0;i<max;i++) {
        char c = str[i];
        if((c == '\n') || (c == '\r') || (c == '\0')) {
            break;
        }
        if(c == ',') {
            number = true;
            continue;
        }
        if(c == ';') {
            number = false;
            dist.push_back(atoi(num.c_str()));
            num.clear();
            continue;
        }
        if(number) {
            num += c;
        }
    }
}

void sort(vector<int>& dist) {
    int len = (int)dist.size();
    for(int i=0;i<len;++i) {
        for(int j=i+1;j<len;++j) {
            if(dist[i] > dist[j]) {
                int t = dist[i];
                dist[i] = dist[j];
                dist[j] = t;
            }
        }
    }
}

void convertToDelta(vector<int>& dist) {
    int len = (int)dist.size();
    for(int i=len-1;i>0;--i) {
        dist[i] -= dist[i-1];
    }
}

void print(const vector<int>& dist) {
    int len = (int)dist.size();
    printf("%d", dist[0]);
    for(int i=1;i<len;++i) {
        printf(",%d", dist[i]);
    }
    printf("\n");
}

void printCities(char* str, int max) {
    vector<int> dist;
    getCities(str, max, dist);
    sort(dist);
    convertToDelta(dist);
    print(dist);
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: RoadTrip <fileContainingTestVectors>\n");
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
        printCities(currentLine, MAX_LINE);
    }
    fclose(fp);
    return 0;
}
