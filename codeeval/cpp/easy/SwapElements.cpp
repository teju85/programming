//
// Challenge name: Swap Elements
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/112/
// Compile       : g++ -Wall -g -o SwapElements SwapElements.cpp
//

#include <stdio.h>
#include <vector>
#include <string>
#define MAX_LINE 1024
using namespace std;

void swap(vector<string>& arr, int src, int dst) {
    int s = (int) arr.size();
    if((src < 0) || (src >= s) || (dst < 0) || (dst >= s)) {
        return;
    }
    string t = arr[src];
    arr[src] = arr[dst];
    arr[dst] = t;
}

void populateVector(char* str, int max, vector<string>& arr) {
    int i;
    string temp;
    for(i=0;i<max;i++) {
        if(str[i] == ':') {
            ++i;
            break;
        }
        if(str[i] == ' ') {
            arr.push_back(temp);
            temp = "";
            continue;
        }
        temp += str[i];
    }
    int src, dst;
    src = dst = 0;
    temp = "";
    for(;i<max;++i) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            sscanf(temp.c_str(), "%d", &dst);
            swap(arr, src, dst);
            break;
        }
        if(str[i] == ' ') {
            continue;
        }
        if(str[i] == ',') {
            sscanf(temp.c_str(), "%d", &dst);
            swap(arr, src, dst);
            temp = "";
            continue;
        }
        if(str[i] == '-') {
            sscanf(temp.c_str(), "%d", &src);
            temp = "";
            continue;
        }
        temp += str[i];
    }
}

void printFinalVector(const vector<string>& arr) {
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
        printf("USAGE: SwapElements <fileContainingTestVectors>\n");
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
        populateVector(currentLine, MAX_LINE, arr);
        printFinalVector(arr);
    }
    fclose(fp);
    return 0;
}
