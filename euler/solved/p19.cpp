//
// Challenge name: Problem 19
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=19
// Compile       : g++ -Wall -g -o p19 p19.cpp
// Run           : ./p19
//

#include <stdio.h>



/**
 * 0  Jan 31
 * 1  Feb 28/29
 * 2  Mar 31
 * 3  Apr 30
 * 4  May 31
 * 5  Jun 30
 * 6  Jul 31
 * 7  Aug 31
 * 8  Sep 30
 * 9  Oct 31
 * 10 Nov 30
 * 11 Dec 31
 */

/**
 * 0 Sun
 * 1 Mon
 * 2 Tue
 * 3 Wed
 * 4 Thu
 * 5 Fri
 * 6 Sat
 */

bool isLeapYear(int year) {
    if((year % 400) == 0) {
        return true;
    }
    if((year % 100) == 0) {
        return false;
    }
    if((year % 4) == 0) {
        return true;
    }
    return false;
}

int numDaysInMonth(int month, int year) {
    switch(month) {
    case 0:
    case 2:
    case 4:
    case 6:
    case 7:
    case 9:
    case 11:
        return 31;
    case 3:
    case 5:
    case 8:
    case 10:
        return 30;
    case 1:
        return (isLeapYear(year)? 29: 28);
    }
    return 0;
}

int firstOfNextMonth(int currentFirstDay, int numDays) {
    return ((currentFirstDay + numDays) % 7);
}

int numSundays;
// return first day for next year
int countSundaysFirstDayInYear(int firstDay, int year) {
    for(int mon=0;mon<12;++mon) {
        if(firstDay == 0) {
            ++numSundays;
        }
        int numdays = numDaysInMonth(mon, year);
        firstDay = firstOfNextMonth(firstDay, numdays);
    }
    return firstDay;
}

int main(int argc, char** argv) {
    // 1st Jan 1901 is Tuesday
    int firstDay = 2;
    numSundays = 0;
    for(int year=1901;year<=2000;++year) {
        firstDay = countSundaysFirstDayInYear(firstDay, year);
    }
    printf("%d\n", numSundays);
    return 0;
}
