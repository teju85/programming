#ifndef __INCLUDED_TOTIENT_H__
#define __INCLUDED_TOTIENT_H__


#include "seive.h"
#include "integers.h"

#ifndef TOTIENT_INT
#define TOTIENT_INT int
#endif


/**
 * @class EulerTotient totient.h
 * @brief Implementation of Euler Totient
 */
class EulerTotient {
public:
    /**
     * @brief Constructor
     * @param num till which the totient needs to be evaluated
     */
    EulerTotient(TOTIENT_INT num);

    /**
     * @brief destructor
     */
    ~EulerTotient();

    /**
     * @brief Get the totient for the given number
     * @param num the number
     * @param the totient value
     */
    TOTIENT_INT get_totient(TOTIENT_INT num);


private:
    /** limit */
    TOTIENT_INT m_num;
    /** the seive */
    eratos m_se;
    /** totient values */
    TOTIENT_INT* m_totient;
};

EulerTotient::EulerTotient(TOTIENT_INT num): m_num(num), m_se(num) {
    m_se.generate_seive();
    m_totient = new TOTIENT_INT[num+1];
    m_totient[0] = 1;
    m_totient[1] = 1;
    for(TOTIENT_INT i=2;i<=num;++i) {
        m_totient[i] = 0;
    }
}

EulerTotient::~EulerTotient() {
    delete m_totient;
}

TOTIENT_INT EulerTotient::get_totient(TOTIENT_INT num) {
    if(m_totient[num] > 0) {
        return m_totient[num];
    }
    if(m_se.is_prime(num)) {
        m_totient[num] = num - 1;
        return m_totient[num];
    }
    TOTIENT_INT i;
    for(i=2;i<num;++i) {
        if(!(num % i)) {
            break;
        }
    }
    TOTIENT_INT t = num / i;
    TOTIENT_INT g = gcd<TOTIENT_INT>(t, i);
    m_totient[num] = m_totient[t] * m_totient[i];
    if(g != 1) {
        m_totient[num] = (m_totient[num] * g) / m_totient[g];
    }
    return m_totient[num];
}


/* DO NOT WRITE ANYTHING BELOW THIS LINE!!! */
#endif // __INCLUDED_TOTIENT_H__
