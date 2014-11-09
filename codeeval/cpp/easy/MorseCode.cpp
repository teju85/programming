//
// Challenge name: Morse Code
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/116/
// Compile       : g++ -Wall -g -o MorseCode MorseCode.cpp
//

#include <stdio.h>
#include <string>
#include <map>
#define MAX_LINE 2048
using namespace std;

map<string,char> code;

void initCode() {
    code[".-"]     = 'A';
    code["-..."]   = 'B';
    code["-.-."]   = 'C';
    code["-.."]    = 'D';
    code["."]      = 'E';
    code["..-."]   = 'F';
    code["--."]    = 'G';
    code["...."]   = 'H';
    code[".."]     = 'I';
    code[".---"]   = 'J';
    code["-.-"]    = 'K';
    code[".-.."]   = 'L';
    code["--"]     = 'M';
    code["-."]     = 'N';
    code["---"]    = 'O';
    code[".--."]   = 'P';
    code["--.-"]   = 'Q';
    code[".-."]    = 'R';
    code["..."]    = 'S';
    code["-"]      = 'T';
    code["..-"]    = 'U';
    code["...-"]   = 'V';
    code[".--"]    = 'W';
    code["-..-"]   = 'X';
    code["-.--"]   = 'Y';
    code["--.."]   = 'Z';
    code["-----"]  = '0';
    code[".----"]  = '1';
    code["..---"]  = '2';
    code["...--"]  = '3';
    code["....-"]  = '4';
    code["....."]  = '5';
    code["-...."]  = '6';
    code["--..."]  = '7';
    code["---.."]  = '8';
    code["----."]  = '9';
    code[".-.-.-"] = '.';
    code["--..--"] = ',';
    code["..--.."] = '?';
}

string decode(char* str, int max) {
    string outStr, temp;
    bool prevSpace = false;
    for(int i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            if(temp != "") {
                outStr += code[temp];
            }
            break;
        }
        if(str[i] == ' ') {
            if(prevSpace) {
                outStr += ' ';
            }
            else {
                outStr += code[temp];
                temp = "";
            }
            prevSpace = true;
        }
        else {
            prevSpace = false;
            temp += str[i];
        }
    }
    return outStr;
}

int main(int argc, char** argv) {
    initCode();
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: MorseCode <fileContainingTestVectors>\n");
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
        string str = decode(currentLine, MAX_LINE);
        printf("%s\n", str.c_str());
    }
    fclose(fp);
    return 0;
}
