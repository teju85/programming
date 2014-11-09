#!/bin/bash



function createReadStr() {
    echo "        char currentLine[MAX_LINE];"
    echo "        currentLine[0] = '\0';"
    echo "        fgets(currentLine, MAX_LINE, fp);"
    echo "        int len = stringLen(currentLine, MAX_LINE);"
    echo "        if(len <= 0) {"
    echo "            continue;"
    echo "        }"
}

function createInput() {
    echo "    FILE* fp;"
    echo "    if(argc != 2) {"
    echo "        printf(\"USAGE: $exe <fileContainingTestVectors>\n\");"
    echo "        return 1;"
    echo "    }"
    echo "    fp = fopen(argv[1], \"r\");"
    echo "    if(fp == NULL) {"
    echo "        printf(\"Failed to open the input file '%s' for reading!\n\", argv[1]);"
    echo "        return 2;"
    echo "    }"
    echo "    while(!feof(fp)) {"
    if [ "$strRead" = "1" ]; then
        createReadStr
    fi
    echo "    }"
    echo "    fclose(fp);"
}

function createStrLen() {
    echo "#define MAX_LINE 1024"
    echo ""
    echo "int stringLen(char* str, int max) {"
    echo "    int i;"
    echo "    for(i=0;i<max;i++) {"
    echo "        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {"
    echo "            str[i] = '\0';"
    echo "            return i;"
    echo "        }"
    echo "    }"
    echo "    return max;"
    echo "}"
}

function code() {
    echo "//"
    echo "// Challenge name: $name"
    echo "// Difficulty    : $diff"
    echo "// Link          : $link"
    echo "// Compile       : g++ -Wall -g -o $exe $source"
    echo "//"
    echo ""
    echo "#include <stdio.h>"
    if [ "$strRead" = "1" ]; then
        createStrLen
    fi
    echo ""
    echo "int main(int argc, char** argv) {"
    if [ "$input" = "1" ]; then
        createInput
    fi
    echo "    return 0;"
    echo "}"
}


echo -n "Challenge name: "
read name
echo -n "Difficulty: "
read diff
echo -n "Link to the challenge: "
read link
echo -n "Name of the exe: "
read exe
echo -n "Read from a file? [0/1]: "
read input
if [ "$input" = "1" ]; then
    echo -n "Reading each line in file as string? [0/1]: "
    read strRead
fi
source="$exe.cpp"
"cd" $diff
code > $source
