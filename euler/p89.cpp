//
// Challenge name: Problem 89
// Difficulty    : medium
// Link          : http://projecteuler.net/index.php?section=problems&id=89
// Compile       : g++ -Wall -g -o p89 p89.cpp
// Run           : ./p89
//

#include <stdio.h>
#include <string.h>
#include <map>
#include <string>
using namespace std;

map<char, int> roman;

void initMap() {
    roman['I'] = 1;
    roman['V'] = 5;
    roman['X'] = 10;
    roman['L'] = 50;
    roman['C'] = 100;
    roman['D'] = 500;
    roman['M'] = 1000;
}

int getInt(const char* str, int len) {
    if(len <= 0) {
        return 0;
    }
    int num = 0;
    for(int i=0;i<len;++i) {
        int val = roman[str[i]];
        int val1 = (i != len-1)? roman[str[i+1]] : 0;
        if(val < val1) {
            num += (val1 - val);
            ++i;
        }
        else {
            num += val;
        }
    }
    return num;
}

void _append(string& str, int& num, char rom) {
    int val = roman[rom];
    while(num >= val) {
        num -= val;
        str += rom;
    }
}

string getRoman(int num) {
    string str("");
    if(num <= 0) {
        return str;
    }
    _append(str, num, 'M');
    _append(str, num, 'D');
    _append(str, num, 'C');
    _append(str, num, 'L');
    _append(str, num, 'X');
    _append(str, num, 'V');
    _append(str, num, 'I');
    return str;
}

int main(int argc, char** argv) {
    initMap();
    printf("%s\n", getRoman(1009).c_str());
    return 0;
}
