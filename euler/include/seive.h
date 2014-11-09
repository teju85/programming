#ifndef __INCLUDED_SEIVE_H__
#define __INCLUDED_SEIVE_H__


#include <stdlib.h>
#include "integers.h"
#include "types.h"


/**
 * @class eratos seive.h
 * @brief Implementation of 'seive of eratosthenes'
 */
class eratos {
public:
    /**
     * @brief Constructor
     * @param _num number of integers for which seive is needed
     */
    eratos(uint32 _num=0);

    /**
     * @brief destructor
     */
    ~eratos();

    /**
     * @brief Generate the seive
     * @param _num number of integers for which seive is needed
     */
    void generate_seive(uint32 _num=0);

    /**
     * @brief Check whether a number is prime or not
     * @param num number to be checked
     * @return true if the 'num' is prime, else false
     */
    bool is_prime(uint32 num) const;

    /**
     * @brief Helper function to print all primes from this simulation
     */
    void print_all_primes() const;

    /**
     * @brief Number of primes in this range
     * @return number of primes
     */
    uint32 num_primes() const;

    /**
     * @brief returns the limit (value of 'N')
     * @return value
     */
    uint32 get_limit() const;

    /**
     * @brief returns the size of the seive (in B)
     * @return size
     */
    uint32 get_size() const;


private:
    /**
     * @brief given a number get it's id in the seive
     * @param num number
     * @return the id of this number in this seive
     */
    uint32 _get_id(uint32 num) const;

    /**
     * @brief given an id, get the corresponding number
     * @param id id for which one needs to look up
     * @return the number
     */
    uint32 _get_num(uint32 id) const;

    /**
     * @brief get mask and the corresponding location for a given number
     * @param num the number
     * @param mask the mask for this number
     * @param pos position for this number in the seive
     */
    void _get_mask_pos(uint32 num, uint32& mask, uint32& pos) const;

    /**
     * @brief mark the number as not prime
     * @param num the number
     */
    void _unmark(uint32 num);

    /**
     * @brief Helper function to clear the state
     */
    void _clear();


    /** find all primes till this number, and it's square root */
    uint32 m_N;
    /** square root of 'N' */
    uint32 m_sqN;
    /** amount of memory needed for the seive */
    uint32 m_size;
    /** the seive */
    uint8 *m_seive;
};


eratos::eratos(uint32 _num) {
    m_N = _num;
    m_seive = NULL;
    if(_num) {
        generate_seive();
    }
}

eratos::~eratos() {
    _clear();
}

void eratos::generate_seive(uint32 _num) {
    uint32 cid, cnum, i, num, cnum2;
    // check
    if(!m_N && !_num) {
        printf("You cannot generate primes from an unitialized seive!\n");
        exit(1);
    }
    // initialization of the seive
    if(_num) {
        m_N = _num;
    }
    m_sqN = sqrt_int<uint32>(m_N);
    m_size = (((m_N >> 1) + 1) >> 3) + 1;
    _clear();
    m_seive = new uint8[m_size];
    // assume all to be primes
    for(i=0;i<m_size;i++) {
        m_seive[i] = 0xff;
    }
    // initialization of local variables
    cid = 0;
    cnum = _get_num(cid);
    // main loop through sift through all primes
    while(cnum <= m_sqN) {
        // find the next prime
        do {
            ++cid;
            cnum = _get_num(cid);
            if(is_prime(cnum)) {
                break;
            }
        } while(cnum <= m_sqN);
        cnum2 = cnum << 1;
        // 'unmark' all the 'odd' multiples of the current prime
        for(i=3,num=i*cnum;num<=m_N;i+=2,num+=cnum2) {
            _unmark(num);
        }
    }
    return;
}

bool eratos::is_prime(uint32 num) const {
    uint32 mask, pos;
    // trivial cases
    if(num <= 1) {
        return false;
    }
    if(num == 2) {
        return true;
    }
    if(!(num & 1)) {
        return false;
    }
    // bound-check
    if(num > m_N) {
        printf("Input can't be greater than limit! '%u', '%u'\n", num, m_N);
        exit(1);
    }
    // refer the seive
    _get_mask_pos(num, mask, pos);
    return (m_seive[pos] & mask);
}

uint32 eratos::num_primes() const {
    uint32 i, n, num, cnt;
    n = m_size << 3;
    for(i=0,cnt=1;i<n;i++) {
        num = _get_num(i);
        if(num > m_N) {
            break;
        }
        if(is_prime(num)) {
            cnt++;
        }
    }
    return cnt;
}

uint32 eratos::_get_id(uint32 num) const {
    if(!(num & 1)) {
        printf("Input can't be even! '%u'\n", num);
        exit(1);
    }
    return (num >> 1);
}

uint32 eratos::_get_num(uint32 id) const {
    if(id == 0) {
        return 2;
    }
    return ((id << 1) + 1);
}

void eratos::_get_mask_pos(uint32 num, uint32& mask, uint32& pos) const {
    if(num > m_N) {
        printf("Input can't be greater than limit! '%u', '%u'\n", num, m_N);
        exit(1);
    }
    pos = _get_id(num);
    mask = 1 << (pos & 0x7);
    pos >>= 3;
    return;
}

void eratos::_unmark(uint32 num) {
    uint32 mask, pos;
    if(num > m_N) {
        printf("Input can't be greater than limit! '%u', '%u'\n", num, m_N);
        exit(1);
    }
    _get_mask_pos(num, mask, pos);
    m_seive[pos] &= (~mask);
    return;
}

void eratos::_clear() {
    if(m_seive != NULL) {
        delete m_seive;
        m_seive = NULL;
    }
}


/* DO NOT WRITE ANYTHING BELOW THIS LINE!!! */
#endif // __INCLUDED_SEIVE_H__
