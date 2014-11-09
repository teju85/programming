#ifndef __INCLUDED_BIGINT_H__
#define __INCLUDED_BIGINT_H__


#include <stdlib.h>
#include <string>
#include <sstream>
#include <iomanip>
#include "types.h"
#include "integers.h"

#ifndef NUMWORDS
    #define NUMWORDS   128
    #define NUMWORDS_1 127
    #define NUMBITS    4096
#endif


/**
 * @class BigInt bigint.h
 * @brief Class for Big integers
 */
class BigInt {
public:
    /**
     * @brief Default constructor
     */
    BigInt() {
        for(int32 i=0;i<NUMWORDS;++i) {
            m_data[i] = 0;
        }
    }

    /**
     * @brief Copy constructor
     * @param in source
     */
    BigInt(const BigInt& in) {
        for(int32 i=0;i<NUMWORDS;++i) {
            m_data[i] = in.m_data[i];
        }
    }

    /**
     * @brief Construct bigint from unsigned 32b int
     * @param in the integer
     */
    BigInt(const uint32 in) { set_uint32(in); }

    /**
     * @brief Construct bigint from unsigned 64b int
     * @param in the integer
     */
    BigInt(const uint64 in) { set_uint64(in); }

    /**
     * @brief Construct a bigint using an array of unsigned ints
     * @param in array
     */
    BigInt(uint32* in) {
        for(int32 i=0;i<NUMWORDS;++i) {
            m_data[i] = in[i];
        }
    }

    /**
     * @brief Destructor
     */
    ~BigInt() {}

    // get the data
    uint32* get_data() { return m_data; }

    /**
     * @brief Set the value of this bigint from unsigned 32b int
     * @param in the integer
     */
    void set_uint32(const uint32 in) {
        m_data[0] = in;
        for(int32 i=1;i<NUMWORDS;i++) {
            m_data[i] = 0;
        }
    }

    /**
     * @brief Set the value of this bigint from unsigned 64b int
     * @param in the integer
     */
    void set_uint64(const uint64 in) {
        m_data[0] = (uint32) in;
        m_data[1] = (uint32) (in >> 32);
        for(int32 i=2;i<NUMWORDS;++i) {
            m_data[i] = 0;
        }
    }

    /**
     * @brief Get the last word (downgrade)
     * @return 32b int
     */
    uint32 to_uint32() { return m_data[0]; }

    /**
     * @brief Convert number to std::string
     * @param dec whether to print in decimal or not [true]
     * @return the std::string
     */
    std::string get_string(bool dec=true) const {
        std::ostringstream oss;
        if(!dec) {   // hexadecimal
            int32 i;
            oss << "0x";
            for(i=NUMWORDS-1;i>=0;--i) {
                oss << std::setfill('0') << std::setw(8) << std::hex
                    << m_data[i] << " ";
            }
            return oss.str();
        }
        BigInt ten(10ULL);
        BigInt temp;
        BigInt ta = *this;
        uint32 digits[NUMWORDS*10];
        int32 i = 0;
        digits[i] = 0;
        if(ta == 0) {
            ++i;
        }
        while(ta != 0) {
            temp = ta % ten;
            digits[i] = temp.to_uint32();
            ta /= ten;
            ++i;
        }
        for(--i;i>=0;--i) {
            oss << digits[i];
        }
        return oss.str();
    }

    /**
     * @brief Addition operation
     * @param a operand1
     * @param b operand2
     * @return a + b
     */
    friend BigInt operator+(const BigInt& a, const BigInt& b) {
        uint32 i, c;
        BigInt res;
        for(i=0,c=0;i<NUMWORDS;++i) {
            res.m_data[i] = a.m_data[i] + b.m_data[i] + c;
            if(c == 1) {
                c = ((res.m_data[i] <= a.m_data[i]) ||
                     (res.m_data[i] <= b.m_data[i]))? 1 : 0;
            }
            else {
                c = ((res.m_data[i] < a.m_data[i]) ||
                     (res.m_data[i] < b.m_data[i]))? 1 : 0;
            }
        }
        return res;
    }

    /**
     * @brief Subtraction operation
     * @param a operand1
     * @param b operand2
     * @return a - b
     */
    friend BigInt operator-(const BigInt& a, const BigInt& b) {
        BigInt res;
        for(uint32 i=0,bor=0;i<NUMWORDS;i++) {
            res.m_data[i] = a.m_data[i] - b.m_data[i] - bor;
            if(bor) {
                bor = (a.m_data[i] <= b.m_data[i])? 1 : 0;
            }
            else {
                bor = (a.m_data[i] < b.m_data[i])? 1 : 0;
            }
        }
        return res;
    }

    /**
     * @brief Multiplication operation
     * @param a operand1
     * @param b operand2
     * @return a * b
     */
    friend BigInt operator*(const BigInt& a, const BigInt& b) {
        BigInt res, ta, tb;
        ta = a;
        tb = b;
        do {
            if(tb.m_data[0] & 1) {
                res += ta;
            }
            tb >>= 1;
            ta <<= 1;
        } while(tb != 0);
        return res;
    }

    /**
     * @brief Division operation
     * @param a operand1
     * @param b operand2
     * @param rem will contain the final remainder at the end
     * @return a / b
     */
    friend BigInt division(const BigInt& a, const BigInt& b, BigInt& rem) {
        BigInt quo, ta, tb;
        int32 cnt;
        // initialization
        ta = a;
        tb = b;
        cnt = 0;
        // check for division by zero
        if(tb == 0) {
            printf("Division-by-zero exception! A=%s B=%s\n",
                   a.get_string().c_str(), b.get_string().c_str());
            exit(1);
        }
        // trivial case
        if(ta == 0) {
            rem.set_uint32(0);
            return quo;
        }
        // work on 'tb'
        while((tb < ta) && ((tb.m_data[NUMWORDS-1] & 0x80000000) == 0)) {
            tb <<= 1;
            ++cnt;
        }
        if(tb > ta) {
            tb >>= 1;
            --cnt;
        }
        // main loop for division
        for(int32 i=0;i<=cnt;++i) {
            if(tb <= ta) {
                ta -= tb;
                tb >>= 1;
                quo <<= 1;
                ++quo;
            }
            else {
                tb >>= 1;
                quo <<= 1;
            }
        }
        rem = ta;
        return quo;
    }

    /**
     * @brief Division operation
     * @param a operand1
     * @param b operand2
     * @return a / b
     */
    friend BigInt operator/(const BigInt& a, const BigInt& b) {
        BigInt rem;
        return division(a, b, rem);
    }

    /**
     * @brief Modulus operation
     * @param a operand1
     * @param b operand2
     * @return a % b
     */
    friend BigInt operator%(const BigInt& a, const BigInt& b) {
        BigInt rem, quo;
        quo = division(a, b, rem);
        return rem;
    }

    /**
     * @brief Addition operation
     * @param in operand
     * @return this += in
     */
    BigInt operator+=(const BigInt& in) {
        return *this = *this + in;
    }

    /**
     * @brief Subtraction operation
     * @param in operand
     * @return this -= in
     */
    BigInt operator-=(const BigInt& in) {
        return *this = *this - in;
    }

    /**
     * @brief Multiplication operation
     * @param in operand
     * @return this *= in
     */
    BigInt operator*=(const BigInt& in) {
        return *this = *this * in;
    }

    /**
     * @brief Division operation
     * @param in operand
     * @return this /= in
     */
    BigInt operator/=(const BigInt& in) {
        BigInt rem;
        *this = division(*this, in, rem);
        return *this;
    }

    /**
     * @brief Modulus operation
     * @param in operand
     * @return this %= in
     */
    BigInt operator%=(const BigInt& in) {
        BigInt rem, quo;
        quo = division(*this, in, rem);
        *this = rem;
        return *this;
    }

    /**
     * @brief post-increment operator
     * @return the current BigInt
     */
    BigInt& operator++() {
        ++m_data[0];
        for(int32 i=1;i<NUMWORDS;++i) {
            if(m_data[i-1] == 0) {
                ++m_data[i];
            }
            else {
                break;
            }
        }
        return *this;
    }

    /**
     * @brief pre-increment operator
     * @param in val
     * @return the current BigInt
     */
    BigInt& operator++(int32 in) {
        ++m_data[0];
        for(int32 i=1;i<NUMWORDS;++i) {
            if(m_data[i-1] == 0) {
                ++m_data[i];
            }
            else {
                break;
            }
        }
        return *this;
    }

    /**
     * @brief Unary minus operator
     * @param in input BigInt
     * @return negated BigInt
     */
    friend BigInt operator-(const BigInt& in) {
        BigInt res = ~in;
        ++res;
        return res;
    }

    /**
     * @brief post-decrement operator
     * @return the current BigInt
     */
    BigInt& operator--() {
        --m_data[0];
        for(int32 i=1;i<NUMWORDS;++i) {
            if(m_data[i-1] == 0xffffffff) {
                --m_data[i];
            }
            else {
                break;
            }
        }
        return *this;
    }

    /**
     * @brief pre-decrement operator
     * @param in val
     * @return the current BigInt
     */
    BigInt& operator--(int32 in) {
        --m_data[0];
        for(int32 i=1;i<NUMWORDS;++i) {
            if(m_data[i-1] == 0xffffffff) {
                --m_data[i];
            }
            else {
                break;
            }
        }
        return *this;
    }

    /**
     * @brief Index operator
     * @param idx index to be picked up
     * @return the data at that index location
     */
    uint32& operator[](int32 idx) {
        if((idx >= 0) && (idx < NUMWORDS)) {
            return m_data[idx];
        }
        else {
            printf("Index out of bounds! '%d' '%d'\n", idx, (NUMWORDS-1));
            exit(1);
        }
    }

    /**
     * @brief Equality operator
     * @param a operand1
     * @param b operand2
     * @return true if they are equal, else false
     */
    friend bool operator==(const BigInt& a, const BigInt& b) {
        for(int32 i=0;i<NUMWORDS;++i) {
            if(a.m_data[i] != b.m_data[i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Equality operator
     * @param a operand1
     * @param b operand2
     * @return true if they are equal, else false
     */
    friend bool operator==(const BigInt& a, uint32 b) {
        if(a.m_data[0] != b) {
            return false;
        }
        for(int32 i=1;i<NUMWORDS;++i) {
            if(a.m_data[i] != 0) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Non-equality operator
     * @param a operand1
     * @param b operand2
     * @return true if they are not equal, else false
     */
    friend bool operator!=(const BigInt& a, const BigInt& b) {
        return !(a == b);
    }

    /**
     * @brief Non-equality operator
     * @param a operand1
     * @param b operand2
     * @return true if they are not equal, else false
     */
    friend bool operator!=(const BigInt& a, uint32 b) {
        return !(a == b);
    }

    /**
     * @brief greater-than-or-equal-to
     * @param a operand1
     * @param b operand2
     * @return true if it is, else false
     */
    friend bool operator>=(const BigInt& a, const BigInt& b) {
        for(int32 i=NUMWORDS-1;i>=0;--i) {
            if(a.m_data[i] > b.m_data[i]) {
                return true;
            }
            else if(a.m_data[i] < b.m_data[i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief lesser-than-or-equal-to
     * @param a operand1
     * @param b operand2
     * @return true if it is, else false
     */
    friend bool operator<=(const BigInt& a, const BigInt& b) {
        for(int32 i=NUMWORDS-1;i>=0;--i) {
            if(a.m_data[i] < b.m_data[i]) {
                return true;
            }
            else if(a.m_data[i] > b.m_data[i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief greater-than
     * @param a operand1
     * @param b operand2
     * @return true if it is, else false
     */
    friend bool operator>(const BigInt& a, const BigInt& b) {
        return !(a <= b);
    }

    /**
     * @brief lesser-than
     * @param a operand1
     * @param b operand2
     * @return true if it is, else false
     */
    friend bool operator<(const BigInt& a, const BigInt& b) {
        return !(a >= b);
    }

    /**
     * @brief bitwise negation
     * @param a num
     * @return bitwise negation of num
     */
    friend BigInt operator~(const BigInt& a) {
        BigInt res;
        for(int32 i=0;i<NUMWORDS;++i) {
            res.m_data[i] = ~a.m_data[i];
        }
        return res;
    }


    /**
     * @brief bitwise and
     * @param in operand
     * @return this &= in
     */
    BigInt& operator&=(const BigInt& in) {
        for(int32 i=0;i<NUMWORDS;++i) {
            m_data[i] &= in.m_data[i];
        }
        return *this;
    }

    /**
     * @brief bitwise or
     * @param in operand
     * @return this |= in
     */
    BigInt& operator|=(const BigInt& in) {
        for(int32 i=0;i<NUMWORDS;++i) {
            m_data[i] |= in.m_data[i];
        }
        return *this;
    }

    /**
     * @brief bitwise xor
     * @param in operand
     * @return this ^= in
     */
    BigInt& operator^=(const BigInt& in) {
        for(int32 i=0;i<NUMWORDS;++i) {
            m_data[i] ^= in.m_data[i];
        }
        return *this;
    }

    /**
     * @brief bitwise and
     * @param a operand1
     * @param b operand2
     * @return a & b
     */
    friend BigInt operator&(const BigInt& a, const BigInt& b) {
        BigInt res(a);
        return res &= b;
    }

    /**
     * @brief bitwise or
     * @param a operand1
     * @param b operand2
     * @return a | b
     */
    friend BigInt operator|(const BigInt& a, const BigInt& b) {
        BigInt res(a);
        return res |= b;
    }

    /**
     * @brief bitwise xor
     * @param a operand1
     * @param b operand2
     * @return a ^ b
     */
    friend BigInt operator^(const BigInt& a, const BigInt& b) {
        BigInt res(a);
        return res ^= b;
    }

    /**
     * @brief right shift
     * @param a num
     * @param shift shift to be performed
     * @return a >> shift
     */
    friend BigInt operator>>(const BigInt& a, uint32 shift) {
        BigInt res;
        uint32 carry, cmask, del, i;
        uint32 max = NUMWORDS << 5;
        int32 intShifts = (int32) (shift >> 5);
        del = NUMWORDS - intShifts;
        // trivial case
        if(shift >= max) {
            return res;
        }
        // integer wise shifts
        for(i=0;i<del;++i) {
            res.m_data[i] = a.m_data[i+intShifts];
        }
        for(;i<NUMWORDS;++i) {
            res.m_data[i] = 0;
        }
        shift -= (intShifts << 5);
        if(!shift) {
            return res;
        }
        // bitwise shifts
        cmask = (1 << shift) - 1;
        del = 32 - shift;
        res.m_data[0] >>= shift;
        for(i=1;i<NUMWORDS;++i) {
            carry = (res.m_data[i] & cmask) << del;
            res.m_data[i-1] |= carry;
            res.m_data[i] >>= shift;
        }
        return res;
    }

    /**
     * @brief left shift
     * @param a num
     * @param shift shift to be performed
     * @return a << shift
     */
    friend BigInt operator<<(const BigInt& a, uint32 shift) {
        BigInt res;
        uint32 carry, cmask, del;
        int32 i;
        uint32 max = NUMWORDS << 5;
        int32 intShifts = (int32) (shift >> 5);
        // trivial case
        if(shift >= max) {
            return res;
        }
        // integer wise shifts
        for(i=NUMWORDS-1;i>=intShifts;i--) {
            res.m_data[i] = a.m_data[i-intShifts];
        }
        for(;i>=0;i--) {
            res.m_data[i] = 0;
        }
        shift -= (intShifts << 5);
        if(!shift) {
            return res;
        }
        del = 32 - shift;
        cmask =  (uint32) (((int32) 0x80000000) >> shift);
        for(i=NUMWORDS-1;i>0;i--) {
            carry = (res.m_data[i-1] & cmask) >> del;
            res.m_data[i] <<= shift;
            res.m_data[i] |= carry;
        }
        res.m_data[0] <<= shift;
        return res;
    }

    /**
     * @brief right shift
     * @param shift shift to be performed
     * @return this >>= shift
     */
    BigInt operator>>=(uint32 shift) {
        return *this = *this >> shift;
    }

    /**
     * @brief left shift
     * @param shift shift to be performed
     * @return this <<= shift
     */
    BigInt operator<<=(uint32 shift) {
        return *this = *this << shift;
    }

    /**
     * @brief fill-up the contents with random integers
     * @param num number of bits [NUMBITS]
     */
    void random(int32 num=NUMBITS) {
        if(num > NUMBITS) {
            printf("Numbits exceed the total available space! '%d' '%d'\n",
                   num, NUMBITS);
            exit(1);
        }
        --num;
        int32 j = num >> 5;
        int32 i = 0;
        for(;i<=j;++i) {
            m_data[i] = rand();
        }
        for(;i<NUMWORDS;++i) {
            m_data[i] = 0;
        }
        i = j;
        j -= (i << 5);
        m_data[i] |= (1 << j);
    }

    /**
     * @brief Scalar multiplication
     * @param val int
     * @return result
     */
    BigInt int_mult(uint32 val) {
        BigInt out;
        uint64 t, t1, car;
        t1 = (uint64) val;
        car = 0;
        for(int32 i=0;i<NUMWORDS;++i) {
            t = (((uint64) m_data[i]) * t1) + car;
            out.m_data[i] = (uint32) t;
            car = t >> 32;
        }
        return out;
    }

    /**
     * @brief sum of digits
     * @return sum
     */
    uint32 digit_sum() const {
        uint32 sum = 0;
        BigInt ten(10ULL);
        BigInt temp;
        BigInt ta = *this;
        while(ta != 0) {
            ta = division(ta, ten, temp);
            sum += temp.to_uint32();
        }
        return sum;
    }

    /**
     * @brief number of digits
     * @return number
     */
    uint32 num_digits() const {
        uint32 num = 0;
        BigInt ten(10ULL);
        BigInt temp;
        BigInt ta = *this;
        while(ta != 0) {
            ta /= ten;
            ++num;
        }
        return num;
    }

private:
    /** big integer in little endian format */
    uint32 m_data[NUMWORDS];
};


#endif // __INCLUDED_BIGINT_H__
///////// DO NOT WRITE ANYTHING BELOW THIS LINE!!! /////////
