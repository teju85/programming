#ifndef __INCLUDED_BIQUADFILTER_CPP__
#define __INCLUDED_BIQUADFILTER_CPP__
/**
 * @file biquadfilter.cpp
 * @brief Contains implementation of biquad low pass filter
 */


namespace ficklemind { namespace tilt {


/** Number of coefficients in the filter */
#define NUM_COEFFICIENTS 2


/**
 * @class BiQuadFilter biquadfilter.cpp
 * @brief Low pass biquad filter
 */
class BiQuadFilter {
public:
    /**
     * @brief Constructor
     * @param Q coefficient?
     * @param fc cutoff frequency
     * @param dT time delta (in s)
     */
    BiQuadFilter(float Q, float fc, float dT);

    /** @brief Destructor */
    ~BiQuadFilter() {}

    /**
     * @brief Initialize the filter with an input value
     * @param x input value
     */
    void initFilter(float x);

    /**
     * @brief Evaluate the current output
     * @param x input value
     * @return the current output of the filter
     */
    float eval(float x);

private:
    /** input coefficients */
    float a[NUM_COEFFICIENTS];
    /** output coefficients */
    float b[NUM_COEFFICIENTS];
    /** input history */
    float x[NUM_COEFFICIENTS];
    /** output history */
    float y[NUM_COEFFICIENTS];
};

}} // namespace


/* DO NOT WRITE ANYTHING BELOW THIS LINE!!! */
#endif // __INCLUDED_BIQUADFILTER_CPP__
