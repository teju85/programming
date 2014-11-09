//
// Challenge name: Simple Sorting
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/91/
// Compile       : g++ -Wall -g -o SimpleSorting SimpleSorting.cpp
//

#include <stdio.h>
#include <string>
#include <vector>
#define MAX_LINE 1024
using namespace std;

void populate(string& str, vector<string>& arr, vector<float>& vals) {
    float f;
    sscanf(str.c_str(), "%f", &f);
    vals.push_back(f);
    arr.push_back(str);
    str = "";
}

void createVector(char* str, int max, vector<string>& arr, vector<float>& vals) {
    string temp;
    for(int i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            populate(temp, arr, vals);
            break;
        }
        if(str[i] == ' ') {
            populate(temp, arr, vals);
            continue;
        }
        temp += str[i];
    }
}

void sortVector(vector<string>& arr, vector<float>& vals) {
    int s = (int)arr.size();
    for(int i=0;i<s;++i) {
        for(int j=i+1;j<s;++j) {
            if(vals[i] < vals[j]) {
                continue;
            }
            float t1 = vals[i];
            vals[i] = vals[j];
            vals[j] = t1;
            string t2 = arr[i];
            arr[i] = arr[j];
            arr[j] = t2;
        }
    }
}

void printVector(const vector<string>& arr) {
    bool first = true;
    for(vector<string>::const_iterator itr=arr.begin();itr!=arr.end();++itr) {
        if(first) {
            printf("%s", itr->c_str());
            first = false;
        }
        else {
            printf(" %s", itr->c_str());
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: SimpleSorting <fileContainingTestVectors>\n");
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
        vector<string> arr;
        vector<float> vals;
        createVector(currentLine, MAX_LINE, arr, vals);
        sortVector(arr, vals);
        printVector(arr);
    }
    fclose(fp);
    return 0;
}
