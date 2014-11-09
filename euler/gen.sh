#!/bin/bash



function fileNeeded() {
    echo "    FILE* fp;"
    echo "    if(argc != 2) {"
    echo "        printf(\"USAGE: $exe <fileContainingTestVectors>\n\");"
    echo "        return 1;"
    echo "    }"
    echo "    fp = fopen(argv[1], \"r\");"
    echo "    if(fp == NULL) {"
    echo "        printf(\"Failed to open '%s' for reading!\n\", argv[1]);"
    echo "        return 2;"
    echo "    }"
    echo "    fclose(fp);"
}

function code() {
    echo "//"
    echo "// Challenge name: $name"
    echo "// Difficulty    : $diff"
    echo "// Link          : $link"
    echo "// Compile       : g++ -Wall -g -o $exe $source"
    echo "// Run           : ./$exe"
    echo "//"
    echo ""
    echo "#include <stdio.h>"
    echo ""
    echo "int main(int argc, char** argv) {"
    if [ "$fileInput" = "1" ]; then
        fileNeeded
    fi
    echo "    return 0;"
    echo "}"
}

echo -n "Problem id: "
read id
name="Problem $id"
link="http://projecteuler.net/index.php?section=problems&id=$id"
exe="p$id"
source="p$id.cpp"
echo -n "Difficulty: "
read diff
echo -n "Read inputs from file? (0/1): "
read fileInput
code > $source
echo "Created source file '$source'"
