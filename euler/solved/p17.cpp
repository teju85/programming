//
// Challenge name: Problem 17
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=17
// Compile       : g++ -Wall -g -o p17 p17.cpp
// Run           : ./p17
//

#include <stdio.h>
#include <string>
using namespace std;


string get_digit(int dig) {
    switch(dig) {
    case 0:   return "Zero";
    case 1:   return "One";
    case 2:   return "Two";
    case 3:   return "Three";
    case 4:   return "Four";
    case 5:   return "Five";
    case 6:   return "Six";
    case 7:   return "Seven";
    case 8:   return "Eight";
    case 9:   return "Nine";
    default:  return "";
    }
}

string get_teens(int teens) {
    switch(teens) {
    case 0:   return "Ten";
    case 1:   return "Eleven";
    case 2:   return "Twelve";
    case 3:   return "Thirteen";
    case 4:   return "Fourteen";
    case 5:   return "Fifteen";
    case 6:   return "Sixteen";
    case 7:   return "Seventeen";
    case 8:   return "Eighteen";
    case 9:   return "Nineteen";
    default:  return "";
    }
}

string get_tens(int tens) {
    int t, d;
    if(tens >= 100) {
        return "";
    }
    t = tens / 10;
    d = tens % 10;
    string str;
    switch(t) {
    case 0:
        str = "";
        break;
    case 1:
        return get_teens(d);
    case 2:
        str = "Twenty";
        break;
    case 3:
        str = "Thirty";
        break;
    case 4:
        str = "Forty";
        break;
    case 5:
        str = "Fifty";
        break;
    case 6:
        str = "Sixty";
        break;
    case 7:
        str = "Seventy";
        break;
    case 8:
        str = "Eighty";
        break;
    case 9:
        str = "Ninety";
        break;
    default:
        str = "";
    }
    if(d) {
        str += get_digit(d);
    }
    return str;
}

string get_hundreds(int num) {
    int tens = num % 100;
    int dig = num / 100;
    string str("");
    if(num <= 999) {
        if(dig) {
            str += get_digit(dig) + "Hundred";
            if(tens) {
                str += "And";
                str += get_tens(tens);
            }
        }
        else {
            str += get_tens(tens);
        }
    }
    return str;
}

string get_number_as_string(int num) {
    if(num == 1000) { //special case just for this problem!
        return "OneThousand";
    }
    return get_hundreds(num);
}

int main(int argc, char** argv) {
    int sum = 0;
    for(int i=1;i<=1000;++i) {
        string str = get_number_as_string(i);
        sum += (int)str.size();
    }
    printf("%d\n", sum);
    return 0;
}
