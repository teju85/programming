#ifndef __INCLUDED_CHARACTERS_H__
#define __INCLUDED_CHARACTERS_H__


#include "integers.h"


/**
 * @brief checks whether the input character is a printable char or not
 * @param c character
 * @return true if it is, else false
 */
bool valid_text(char c) {
    return ((c == '\n') || ((c >= ' ') && (c <= '~')) || (c == '\t'));
}

/**
 * @brief checks whether the input character is a sigit or not
 * @param c character
 * @return true if it is, else false
 */
bool is_digit(char c) {
    return ((c >= '0') && (c <= '9'));
}

/**
 * @brief Gets the int-value of the input character digit
 * @param c character which is a digit
 * @return int-value (if it is not a digit '-1' is returned
 */
int char2digit(char c) {
    if(is_digit(c)) {
        return ((int)(c - '0'));
    }
    return -1;
}

/**
 * @brief Reverse the string
 * @param str the string
 * @param s start location for reversal
 * @param e end location for reversal
 */
void reverse_str(char* str, int s, int e) {
    for(;s<e;++s,--e) {
        swap<char>(str[s], str[e]);
    }
}

/**
 * @brief Finds out the sum of all the characters in the string
 * @param str the string
 * @param len number of characters in the string
 * @return the sum
 */
int sum_of_alphabets(const char* str, int len) {
    int sum = 0;
    for(int j=0;j<len;++j) {
        if((str[j] >= 'A') && (str[j] <= 'Z')) {
            sum += (int) (str[j] - 'A' + 1);
        }
        else if((str[j] >= 'a') && (str[j] <= 'z')) {
            sum += (int) (str[j] - 'a' + 1);
        }
    }
    return sum;
}


/* DO NOT WRITE ANYTHING BELOW THIS LINE!!! */
#endif // __INCLUDED_CHARACTERS_H__
