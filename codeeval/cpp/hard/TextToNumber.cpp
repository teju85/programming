//
// Challenge name: Text to Number
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/110/
// Compile       : g++ -Wall -g -o TextToNumber TextToNumber.cpp
//

#include <stdio.h>
#include <map>
#include <string>
#define MAX_LINE 1024
using namespace std;
#define INT long long int

map<string,INT> numberMap;

void initMap() {
    numberMap["zero"] = 0;
    numberMap["one"] = 1;
    numberMap["two"] = 2;
    numberMap["three"] = 3;
    numberMap["four"] = 4;
    numberMap["five"] = 5;
    numberMap["six"] = 6;
    numberMap["seven"] = 7;
    numberMap["eight"] = 8;
    numberMap["nine"] = 9;
    numberMap["eleven"] = 11;
    numberMap["twelve"] = 12;
    numberMap["thirteen"] = 13;
    numberMap["fourteen"] = 14;
    numberMap["fifteen"] = 15;
    numberMap["sixteen"] = 16;
    numberMap["seventeen"] = 17;
    numberMap["eighteen"] = 18;
    numberMap["nineteen"] = 19;
    numberMap["twenty"] = 20;
    numberMap["thirty"] = 30;
    numberMap["forty"] = 40;
    numberMap["fifty"] = 50;
    numberMap["sixty"] = 60;
    numberMap["seventy"] = 70;
    numberMap["eighty"] = 80;
    numberMap["ninety"] = 90;
}

INT word2int(const string& s) {
    map<string,INT>::const_iterator itr = numberMap.find(s);
    if(itr == numberMap.end()) {
        return 0;
    }
    return itr->second;
}

INT text2num(char* str, int max) {
    INT mill = 0;
    INT thou = 0;
    INT hund = 0;
    INT sum = 0;
    bool isNegative = false;
    string temp;
    for(int i=0;i<max;i++) {
        if((str[i] == ' ') || (str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            if(temp == "negative") {
                isNegative = true;
            }
            else if(temp == "hundred") {
                sum *= 100;
            }
            else if(temp == "thousand") {
                thou = sum * 1000;
                sum = 0;
            }
            else if(temp == "million") {
                mill = sum * 1000000;
                sum = 0;
            }
            else {
                sum += word2int(temp);
            }
            if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
                break;
            }
            temp = "";
            continue;
        }
        temp += str[i];
    }
    sum += (mill + thou + hund);
    sum *= (isNegative)? -1 : 1;
    return sum;
}

int main(int argc, char** argv) {
    initMap();
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: TextToNumber <fileContainingTestVectors>\n");
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
        printf("%lld\n", text2num(currentLine, MAX_LINE));
    }
    fclose(fp);
    return 0;
}
