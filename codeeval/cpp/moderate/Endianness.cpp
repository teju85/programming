//
// Challenge name: Endianness
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/15/
// Compile       : g++ -Wall -g -o Endianness Endianness.cpp
//

#include <stdio.h>

int main(int argc, char** argv) {
    char* ptr;
    unsigned int i = 0x00000055;
    ptr = (char*) &i;
    if(ptr[0] == 0x55) {
        printf("LittleEndian\n");
    }
    else {
        printf("BigEndian\n");
    }
    return 0;
}
