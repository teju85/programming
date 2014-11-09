#ifndef __INCLUDED_COMPARISONS_H__
#define __INCLUDED_COMPARISONS_H__


template <typename T>
T min2(T& a, T& b) {
    return ((a < b)? a : b);
}

template <typename T>
T max2(T& a, T& b) {
    return ((a > b)? a : b);
}


template <typename T>
T min3(T& a, T& b, T& c) {
    T temp = min2(a, b);
    return min2(temp, c);
}

template <typename T>
T max3(T& a, T& b, T& c) {
    T temp = max2(a, b);
    return max2(temp, c);
}


/* DO NOT WRITE ANYTHING BELOW THIS LINE!!! */
#endif // __INCLUDED_COMPARISONS_H__
