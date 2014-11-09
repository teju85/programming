#ifndef __INCLUDED_INTEGERS_H__
#define __INCLUDED_INTEGERS_H__


#include <vector>


/**
 * @brief function to find integer square root
 * @param in integer
 * @return square root of 'in'
 */
template <typename T>
T sqrt_int(T in) {
    T out;
    in = (in + 1) >> 1;
    for(out=0;in>out;in-=out++);
    return out;
}

/**
 * @brief Tells whether the input integer is a perfect square or not
 * @param in integer
 * @return true if it is a perfect square, else false
 */
template <typename T>
bool is_perfect_square(T in) {
    T sq_rt = sqrt_int<T>(in);
    return (in == (sq_rt * sq_rt));
}

/**
 * @brief Finds the gcd of 2 integers
 * @param a number 1
 * @param b number 2
 * @return gcd of 'a' and 'b'
 */
template <typename T>
T gcd(T a, T b) {
    T g;
    do {
        g = b % a;
        b = a;
        a = g;
    } while(g != 0);
    return b;
}

/**
 * @brief Finds the lcm of 2 integers
 * @param a number 1
 * @param b number 2
 * @return lcm of 'a' and 'b'
 */
template <typename T>
T lcm(T a, T b) {
    return ((a * b) / gcd<T>(a, b));
}

/**
 * @brief Checks whether the input integer is a prime or not
 * @param a integer
 * @return true if it is, else false
 */
template <typename T>
T is_prime(T a) {
    if(!(a % 2)) {
        return false;
    }
    T sq = sqrt_int(a);
    for(T i=3;i<=sq;i+=2) {
        if(!(a % i)) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Evaluates the number of divisors of the input integer
 * @param a integer
 * @return number of divisors of the input integer
 */
template <typename T>
T num_divisors(T a) {
    if(a <= 1) {
        return 1;
    }
    if((a == 2) || (a == 3)) {
        return 2;
    }
    T no = 0;
    T k = a;
    for(T j=1;j<k;++j) {
        if(!(a % j)) {
            k = a / j;
            no += (k > j)? 2 : 1;
        }
    }
    return no;
}

/**
 * @brief Evaluates the sum of divisors of the input number
 * @param a integer
 * @return sum
 */
template <typename T>
T sum_of_divisors(T a) {
    if(a <= 1) {
        return 1;
    }
    if(a == 2) {
        return 3;
    }
    if(a == 3) {
        return 4;
    }
    T sum = 0;
    T k = a;
    for(T j=1;j<k;++j) {
        if(!(a % j)) {
            k = a / j;
            sum += (k > j)? (k + j) : j;
        }
    }
    return sum;
}

/**
 * @brief Evaluates the sum of 'proper' divisors of the input number
 * @param a integer
 * @return sum
 */
template <typename T>
T sum_of_proper_divisors(T a) {
    if(a <= 3) {
        return 1;
    }
    return (sum_of_divisors<T>(a) - a);
}

/**
 * @brief Finds whether the input integer is a palindrome or not
 * @param a integer
 * @return true if it is, else false
 */
template <typename T>
bool is_palindrome(T a) {
    T i, j, first, last;
    // number of digits
    j = 10;
    for(i=1;a/j;++i,j*=10);
    j /= 10;
    // palindrome check
    for(;i>0;i-=2,j/=100) {
        first = a / j;
        last = a % 10;
        if(first != last) {
            return false;
        }
        a = (a - (first * j)) / 10;
    }
    return true;
}

/**
 * @brief Finds the sum of digits of the input integer
 * @param n integer
 * @return sum of its digits
 */
template <typename T>
T sum_of_digits(T n) {
    T sum = 0;
    for(T i=0;n;++i,n/=10) {
        sum += (n % 10);
    }
    return sum;
}

/**
 * @brief Finds the product of digits of the input integer
 * @param n integer
 * @return product of its digits
 */
template <typename T>
T product_of_digits(T n) {
    T prod = 1;
    for(T i=0;n;++i,n/=10) {
        prod *= (n % 10);
    }
    return prod;
}

/**
 * @brief Finds the sum of square of digits of the input integer
 * @param n integer
 * @return sum of square of its digits
 */
template <typename T>
T sum_of_square_of_digits(T n) {
    T sum = 0;
    for(T i=0;n;++i,n/=10) {
        T d = n % 10;
        sum += (d * d);
    }
    return sum;
}

/**
 * @brief Finds the sum of integers from 1..n
 * @param n integer
 * @return sum of 1..n
 */
template <typename T>
T triangle_sum(T n) {
    return ((n * (n + 1)) >> 1);
}

/**
 * @brief Tells whether the input integer is a triangle number or not
 * @param in integer
 * @return true if it is, else false
 *
 * Solving n^2 + n - 2*k = 0  ==>  n = (-1 +/- sqrt(1 + 8*k)) / 2
 * Now, from this equation, one can easily deduce:
 *  . (1 + 8*k) must be a perfect square
 *  . sqrt(1 + 8*k) must be odd
 */
template <typename T>
bool is_triangle_num(T in) {
    T n1 = 1 + (in << 3);
    T n1_sqrt = sqrt_int<T>(n1);
    T n1d = n1_sqrt * n1_sqrt;
    if(n1 != n1d) {
        return false;
    }
    return (n1_sqrt & 0x1);
}

/**
 * @brief Finds the sum of square of integers from 1..n
 * @param n integer
 * @return sum of squares of 1..n
 */
template <typename T>
T sum_of_squares(T n) {
    return ((n * (n + 1) * ((n << 1) + 1)) / 6);
}

/**
 * @brief Swaps the 2 variables
 * @param a variable 1
 * @param b variable 2
 */
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

/**
 * @brief Tells whether the input number is PO2 or not
 * @param a integer
 * @return true if it is PO2, else false
 */
template <typename T>
bool is_po2(T& a) {
    return (!(a & (a - 1)));
}

/**
 * @brief Finds the absolute value for the input number
 * @param a the number
 * @return the magnitude
 */
template <typename T>
T absolute(T a) {
    return (a > 0)? a : -a;
}

/**
 * @brief Finds the Euler Totient for the given number
 * @param a number
 * @return the totient
 */
template <typename T>
T euler_totient(T a) {
    std::vector<T> multiples(a, 0);
    T num = 1;  // '1' is always relatively prime to all numbers
    for(T i=2;i<a;++i) {
        if(multiples[i]) {
            continue;
        }
        if(gcd<T>(a, i) == 1) {
            ++num;
        }
        else {
            for(T j=i;j<a;j+=i) {
                multiples[j] = 1;
            }
        }
    }
    return num;
}

/**
 * @brief Finds whether the given 2 numbers are permutations of each other
 * @param a number1
 * @param b number2
 * @return true if they are, else false
 */
template <typename T>
bool is_permutation(T a, T b) {
#define LEN 10
    int hista[LEN];
    int histb[LEN];
    for(int i=0;i<LEN;++i) {
        hista[i] = histb[i] = 0;
    }
    while(a) {
        T t = a % 10;
        ++hista[t];
        a /= 10;
    }
    while(b) {
        T t = b % 10;
        ++histb[t];
        b /= 10;
    }
    for(int i=0;i<LEN;++i) {
        if(hista[i] != histb[i]) {
            return false;
        }
    }
    return true;
#undef LEN
}

//TODO: need to 'templatize' this!!!!!!!!!!!!!
/**
 * @brief Fast integer square root
 * @param val the input
 * @return square of 'val'
 */
// REF: http://www.azillionmonkeys.com/qed/ulerysqroot.pdf
unsigned int fast_sqrt_uint(unsigned int val) {
    unsigned int temp;
    unsigned int g = 0;
    unsigned int bshft = 15;
    unsigned int b = 1 << bshft;
    do {
        if(val >= (temp = (((g << 1) + b)<<bshft--))) {
            g += b;
            val -= temp;
        }
    } while (b >>= 1);
    return g;
}

//TODO: need to 'templatize' this!!!!!!!!!!!!!
/**
 * @brief Checks whether the input integer is perfect square or not
 * @param val the input
 * @return true if it is, else false
 */
bool fast_is_perfect_square_uint(unsigned int val) {
    unsigned int s = fast_sqrt_uint(val);
    return ((s * s) == val);
}

/**
 * @brief Checks whether the given number is pentagonal or not
 * @param num the number
 * @return true if it is pentagonal, else false
 */
template <typename T>
bool is_pentagonal(T num) {
    T s = 1 + (24 * num);
    T sq = (T)fast_sqrt_uint((unsigned int)s);
    if((sq * sq) != s) {
        return false;
    }
    return !((sq + 1) % 6);
}

/**
 * @brief Gets the pentagonal value for the input number
 * @param num the number
 * @return pentagonal value
 */
template <typename T>
T pentagonal(T num) {
    return (((3 * num * num) - num) >> 1);
}

/**
 * @brief Find sum of squares of all integers in the range, both inclusive
 * @param m start range
 * @param n end range
 * @return the sum
 */
template <typename T>
T sumOfSquaresBetween(T m, T n) {
    T valn = n * (n + 1) * ((n << 1) + 1);
    T valm = (m - 1) * m * ((m << 1) - 1);
    T val = (valn - valm) / 6;
    return val;
}


/* DO NOT WRITE ANYTHING BELOW THIS LINE!!! */
#endif // __INCLUDED_INTEGERS_H__
