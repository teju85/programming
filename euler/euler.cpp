
#include <map>
#include "include/integers.h"

#ifndef TOT_INT
#define TOT_INT int
#endif


/**
 * @class EulerTotient euler_totient.h
 * @brief Computes euler-totient using memoization
 */
class EulerTotient {
public:
    /**
     * @brief Constructor
     */
    EulerTotient(): m_tot() {
        m_tot[0] = 0;
        m_tot[1] = 1;
        m_tot[2] = 1;
        m_tot[3] = 2;
    }

    /**
     * @brief Destructor
     */
    ~EulerTotient() {}

    /**
     * @brief Calculates euler-totient
     * @param num number of interest
     * @return totient
     */
    TOT_INT etot(TOT_INT num) {
        if(m_tot.find(num) != m_tot.end()) {
            return m_tot[num];
        }
        TOT_INT t;
        if((num & 0x3) == 0) {
            m_tot[num] = t = (etot(num >> 1)) << 1;
        }
        else if((num & 0x3) == 2) {
            m_tot[num] = t = etot(num >> 1);
        }
        else {
            m_tot[num] = t = euler_totient<TOT_INT>(num);
        }
        return t;
    }

    /**
     * @brief Calculates euler-totient of the product of 2 numbers
     * @param m number 1
     * @param n number 2
     * @return totient
     */
    TOT_INT etot(TOT_INT m, TOT_INT n) {
        TOT_INT num = m * n;
        if(m_tot.find(num) != m_tot.end()) {
            return m_tot[num];
        }
        TOT_INT t, d;
        d = gcd<TOT_INT>(m, n);
        m_tot[num] = t = etot(m) * etot(n) * d / etot(d);
        return t;
    }


private:
    /** storing the previously calculated values */
    std::map<TOT_INT, TOT_INT> m_tot;
};
