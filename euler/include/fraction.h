#ifndef __INCLUDED_FRACTION_H__
#define __INCLUDED_FRACTION_H__
/**
 * @file fraction.h
 * @brief Contains high-school division function
 */


#include <string>
#include <vector>


/**
 * @brief Performs high-school division for calculating the inverse
 * @param num the number whose inverse is being sought
 * @param str string representation of the fraction
 * @return true if the division terminates, else false
 */
template <typename T>
bool takeInverse(T num, std::string& str) {
    std::vector<T> quos;
    std::vector<T> rems;
    if(num <= 0) {
        str = "";
        return false;
    }
    if(num == 1) {
        str = "1";
        return true;
    }
    str = "0.";
    T quo = 10;
    while(true) {
        while(quo < num) {
            quo *= 10;
            str += '0';
            quos.push_back(0);
            rems.push_back(quo);
        }
        T rem = quo % num;
        quo /= num;
        if(rem <= 0) {
            str += (char)('0' + quo);
            return true;
        }
        // find cycle
        T iter = (T) quos.size();
        bool cycle = false;
        for(T i=0;i<iter;++i) {
            if((quo == quos[i]) && (rem == rems[i])) {
                cycle = true;
                break;
            }
        }
        str += (char)('0' + quo);
        if(cycle) {
            return false;
        }
        quos.push_back(quo);
        rems.push_back(rem);
        quo = rem * 10;
    }
    return false;  // need to keep the compiler happy!
}


/* DO NOT WRITE ANYTHING BELOW THIS LINE!!! */
#endif // __INCLUDED_FRACTION_H__
