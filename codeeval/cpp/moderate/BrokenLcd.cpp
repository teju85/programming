//
// Challenge name: Broken Lcd
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/179/
// Compile       : g++ -Wall -g -o BrokenLcd BrokenLcd.cpp
//

#include <stdio.h>
#include <string.h>
#include <map>
#include <vector>
#include <string>
using namespace std;
#define NUM_LCDS   12
#define NUM_PARTS  8
#define STR_LEN    32

map<char, string> digits;
void initializeDigits() {
    digits['0'] = "11111100";
    digits['1'] = "01100000";
    digits['2'] = "11011010";
    digits['3'] = "11110010";
    digits['4'] = "01100110";
    digits['5'] = "10110110";
    digits['6'] = "10111110";
    digits['7'] = "11100000";
    digits['8'] = "11111110";
    digits['9'] = "11110110";
}


struct Segment {
    Segment() {
    }

    ~Segment() {
    }

    bool read(FILE* fp) {
        bool valid = true;
        for(int j=0;j<NUM_PARTS;++j) {
            if(fscanf(fp, "%c", &(seg[j])) != 1) {
                valid = false;
                break;
            }
        }
        return valid;
    }

    bool isPrintable(const string& str) const {
        for(int j=0;j<NUM_PARTS;++j) {
            if((seg[j] == '0') && (str[j] == '1')) {
                return false;
            }
        }
        return true;
    }

private:
    char seg[NUM_PARTS];
};


struct Panel {
    Panel() {
    }

    ~Panel() {
    }

    bool read(FILE* fp) {
        for(int i=0;i<NUM_LCDS;++i) {
            if(!lcd[i].read(fp)) {
                return false;
            }
            // space between 2 numbers
            char tmp;
            fscanf(fp, "%c", &tmp);
        }
        fscanf(fp, "%s", num);
        len = strlen(num);
        if(len <= 0) {
            return false;
        }
        // last newline
        char tmp;
        fscanf(fp, "%c", &tmp);
        return true;
    }

    bool isPrintable() const {
        vector<string> out = getNumber();
        // find the first starting position
        int lcdPos = 0;
        while(lcdPos < NUM_LCDS) {
            if(canBePrintedFrom(lcdPos, out)) {
                return true;
            }
            ++lcdPos;
        }
        return false;
    }

private:
    bool canBePrintedFrom(int lcdPos, const vector<string>& out) const {
        int outLen = (int)out.size();
        int numPos = 0;
        for(;lcdPos<NUM_LCDS&&numPos<outLen;++lcdPos,++numPos) {
            if(!lcd[lcdPos].isPrintable(out[numPos])) {
                return false;
            }
        }
        if((numPos == outLen) && (lcdPos <= NUM_LCDS)) {
            return true;
        }
        return false;
    }

    vector<string> getNumber() const {
        vector<string> out;
        for(int i=0;i<len;++i) {
            string str;
            // first number is .!
            if(num[i] == '.') {
                str = "00000001";
            }
            else {
                str = digits[num[i]];
                if(num[i+1] == '.') {
                    str[NUM_PARTS-1] = '1';
                    ++i;
                }
            }
            out.push_back(str);
        }
        return out;
    }

    Segment lcd[NUM_LCDS];
    char num[STR_LEN];
    int len;
};


int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: BrokenLcd <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    initializeDigits();
    while(!feof(fp)) {
        Panel p;
        if(!p.read(fp)) {
            continue;
        }
        printf("%d\n", p.isPrintable()? 1 : 0);
    }
    fclose(fp);
    return 0;
}
