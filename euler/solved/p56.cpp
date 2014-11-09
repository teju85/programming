//
// Challenge name: Problem 56
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=56
// Compile       : g++ -Wall -g -o p56 p56.cpp
// Run           : ./p56
//

#include <stdio.h>

#define NUM_INTS 200
class LargeInt {
public:
    /**
     * @brief Constructor
     * @param val initial value
     */
    LargeInt(int val) {
        for(int i=0;i<4;++i) {
            digits[i] = val >> (i << 3);
        }
        for(int i=4;i<NUM_INTS;++i) {
            digits[i] = 0;
        }
    }

    /**
     * @brief Destructor
     */
    ~LargeInt() {
    }

    /**
     * @brief Sum of digits
     * @return sum
     */
    int digit_sum() const {
        int sum = 0;
        for(int i=0;i<NUM_INTS;++i) {
            sum += digits[i];
        }
        return sum;
    }

    /**
     * @brief Multiply the value contained
     * @param val multiplier
     */
    void multiply(int val) {
        int carry = 0;
        int t;
        for(int i=0;i<NUM_INTS;++i) {
            t = (digits[i] * val) + carry;
            digits[i] = t % 10;
            carry = t / 10;
        }
    }

private:
    /** each of the digits in the number */
    char digits[NUM_INTS];
};


int main(int argc, char** argv) {
    int max = 0;
    for(int a=91;a<=99;++a) {
        LargeInt li(1);
        for(int i=1;i<=90;++i) {
            li.multiply(a);
        }
        for(int b=91;b<=99;++b) {
            li.multiply(a);
            int sum = li.digit_sum();
            //printf("a=%d b=%d sum=%d\n", a, b, sum);
            if(sum > max) {
                max = sum;
            }
        }
    }
    printf("%d\n", max);
    return 0;
}
