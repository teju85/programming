#!/bin/bash
# COMMENTS:
#   Handy script to compile and run the Project-Euler source code
#
# USAGE:
#   run.sh <srcFile>
#    <srcFile>    Source file to be compiled and executed
#                 You can ignore the trailing '.cpp' from this file name
#



# inputs
src1=$1
status="0"
if [ "$src1" = "" ]; then
    echo "USAGE: run.sh <srcFile>"
    exit 1
fi
if [ ! -e "$src1" ]; then
    src="$src1.cpp"
else
    src=$src1
fi
if [ ! -e "$src" ]; then
    echo "Input source file '$src' does not exist!"
    exit 1
fi

# compilation command
com=`grep Compile "$src" | sed -e 's/^\/\/ Compile       : //'`
# run command
run=`grep Run     "$src" | sed -e 's/^\/\/ Run           : //'`

# compilation
if [ "$com" != "" ]; then
    echo "Compilation:  $com"
    $com
    status=$?
fi

# execution
if [ "$run" = "" ]; then
    echo "Source file '$src' doesnot have 'Run' command in it!"
    exit 1
fi
if [ "$status" = "0" ]; then
    echo "Running: $run"
    time $run
    status=$?
fi

# final
exit $status
