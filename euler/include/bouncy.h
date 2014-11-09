#ifndef __INCLUDED_BOUNCY_H__
#define __INCLUDED_BOUNCY_H__
/**
 * @file bouncy.h
 * @brief Contains implementation to find bouncy numbers
 */


/**
 * @enum BouncyType bouncy.h
 * @brief Type of numbers
 */
enum BouncyType {
    /** increasing number (from left-to-right) */
    INCREASING = 0,
    /** decreasing number (from left-to-right) */
    DECREASING,
    /** neither increasing nor decreasing number */
    BOUNCY,
    /** unknown state (mostly unused) */
    UNKNOWN_TYPE
};


/**
 * @brief Converts bouncytype to string
 * @param type bouncy type
 * @return string
 */
const char* bouncytype2str(BouncyType type) {
    switch(type) {
    case INCREASING:   return "INCREASING";
    case DECREASING:   return "DECREASING";
    case BOUNCY:       return "BOUNCY";
    default:           return "UNKNOWN_TYPE";
    }
}


/**
 * @brief Checks for bouncy numbers
 * @param num the number
 * @return type of number
 */
template <typename T>
BouncyType get_bouncy_type(T num) {
    T prev = num % 10;
    BouncyType type = UNKNOWN_TYPE;
    num /= 10;
    while(num) {
        T pres = num % 10;
        if(type == UNKNOWN_TYPE) {
            if(pres < prev) {
                type = INCREASING;
            }
            else if(pres > prev) {
                type = DECREASING;
            }
        }
        else if(type == INCREASING) {
            if(pres > prev) {
                type = BOUNCY;
                return type;
            }
        }
        else if(type == DECREASING) {
            if(pres < prev) {
                type = BOUNCY;
                return type;
            }
        }
        num /= 10;
        prev = pres;
    }
    if(type == UNKNOWN_TYPE) {
        type = INCREASING;
    }
    return type;
}


/**
 * @brief Checks whether the given number is bouncy or not
 * @param num the number
 * @return true if it is bouncy, else false
 */
template <typename T>
bool is_bouncy(T num) {
    // there can't be any bouncy numbers less than 100
    if(num < 100) {
        return false;
    }
    return (get_bouncy_type<T>(num) == BOUNCY);
}


/* DO NOT WRITE ANYTHING BELOW THIS LINE!!! */
#endif // __INCLUDED_BOUNCY_H__
