#!/bin/bash
# COMMENTS:
#   Utility script to check the current status
#
# USAGE:
#   ./status.sh
#


solved=`ls solved/*.cpp | wc -l`
unsolved=`ls *.cpp | wc -l`
echo "NUM SOLVED:   $solved"
echo "NUM UNSOLVED: $unsolved"
