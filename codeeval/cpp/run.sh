#!/bin/bash
#
# USAGE: ./run.sh <src> [<dontPrintInput>]
#


src=$1
dontPrintInput=$2
dir=`dirname $src`
"cd" $dir
source=`basename $src`
exe=`echo $source | sed -e 's/\.cpp$//'`

rm="rm -vf"
test="test_$exe"
cmd=`grep "Compile" $source | sed -e 's/\/\/ Compile       : //'`
$cmd
status=$?
if [ "$status" != "0" ]; then
    exit $status
fi
s=`date +%s.%N`
if [ -e $test ]; then
    if [ "$dontPrintInput" != "1" ]; then
        echo "INPUT:"
        cat $test
        echo
    fi
    echo
    echo "OUTPUT:"
    $exe $test
    status=$?
else
    $exe
    status=$?
fi
e=`date +%s.%N`
echo -n "Time taken (in s): "
echo "$e - $s" | bc
find . -name "*.exe" | xargs -r $rm
find . -name "*~" -o -name ".*~" | xargs -r $rm
$rm $exe
exit $status
