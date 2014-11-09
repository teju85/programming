#ifndef __INCLUDED_PERMUTE_H__
#define __INCLUDED_PERMUTE_H__


#include "integers.h"


// REF: http://www.freewebs.com/permute/quickperm.html
/**
 * @class Permute permute.h
 * @brief Class to permute data
 */
class Permute {
public:
    /**
     * @brief Constructor
     * @param len length of the data (in B)
     */
    Permute(int len): m_len(len), m_num(0), m_idx1(0), m_idx2(0) {
        m_data = new char[m_len];
        m_prim = new char[m_len];
        for(int i=0;i<m_len;++i) {
            m_data[i] = i;
            m_prim[i] = 0;
        }
    }

    /**
     * @brief Destructor
     */
    ~Permute() {
        if(m_data != NULL) {
            delete m_data;
            m_data = NULL;
        }
    }

    /**
     * @brief This'll give the number of permutations performed so far
     * @return number
     *
     * Calling this function after the end of all permutations will give
     * the total number of permutations
     */
    int num_permutes() const {
        return m_num;
    }

    /**
     * @brief Gets the next permutation
     * @param display whether or not to display the permuted data [false]
     * @return the permuted data
     *
     * NOTE: the data will be 'NULL', if we have generated all permutations.
     * Else, it will be of length 'len'.
     */
    const char* next(bool display=false) {
        bool permuted;
        const char* data;
        while(true) {
            // if it is going for the 'next index', then the function
            // would return the same permutation as the previous.
            // So, call the function again to get the next permutation
            data = _get_next(display, permuted);
            if(data == NULL) {
                break;
            }
            if(permuted) {
                break;
            }
        }
        return data;
    }


private:

    /**
     * @brief Gets the next permutation
     * @param display whether or not to display the permuted data
     * @param permuted returns 'true' if there was permutation performed
     * @return the permuted data
     *
     * NOTE: the data will be 'NULL', if we have generated all permutations.
     * Else, it will be of length 'len'.
     */
    const char* _get_next(bool display, bool& permuted) {
        permuted = true;
        // first permutation
        if(!m_num) {
            ++m_num;
            ++m_idx1;
            if(display) {
                _display_data();
            }
            return m_data;
        }
        // end of permutation
        if(m_idx1 >= m_len) {
            permuted = false;
            return NULL;
        }
        // swap
        if(m_prim[m_idx1] < m_idx1) {
            m_idx2 = (m_idx1 & 0x1) * m_prim[m_idx1];
            swap<char>(m_data[m_idx1], m_data[m_idx2]);
            ++(m_prim[m_idx1]);
            m_idx1 = 1;
            ++m_num;
            if(display) {
                _display_data();
            }
        }
        // next index
        else {
            m_prim[m_idx1] = 0;
            ++m_idx1;
            permuted = false;
        }
        return m_data;
    }

    /**
     * @brief Helper function to display the data
     */
    void _display_data() const {
        printf("%8d --> ", m_num);
        for(int i=0;i<m_len;++i) {
            printf("%d ", (int)(m_data[i]));
        }
        printf("\n");
    }

    /** length of the array (in B) */
    int m_len;
    /** permutation counter */
    int m_num;
    /** index1 to be swapped */
    int m_idx1;
    /** index2 to be swapped */
    int m_idx2;
    /** data array to be permuted */
    char* m_data;
    /** primary controller array */
    char* m_prim;
};


/* DO NOT WRITE ANYTHING BELOW THIS LINE!!! */
#endif // __INCLUDED_PERMUTE_H__
