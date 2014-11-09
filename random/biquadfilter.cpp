#include <math.h>
#include "biquadfilter.h"

namespace ficklemind { namespace tilt {

BiQuadFilter::BiQuadFilter(float Q, float fc, float dT):
    a[0](0.0f), a[1](0.0f), b[1](0.0f), b[2](0.0f),
    x[0](0.0f), x[1](0.0f), y[0](0.0f), y[1](0.0f) {
    float iQ = 1.0f / Q;
    float K = tanf(float(M_PI) * fc * dT);
    float iD = 1.0f / ((K * K) + (K * iQ) + 1);
    a[0] = K * K * iD;
    a[1] = 2.0f * a[0];
    b[0] = 2.0f * ((K * K) - 1) * iD;
    b[1] = ((K * K) - (K * iQ) + 1) * iD;
}

void BiQuadFilter::initFilter(float x) {
    x[0] = x[1] = x;
    y[0] = y[1] = x;
}

float BiQuadFilter::eval(float x) {
    float y = ((x + x[1]) * a[0]) + (x[0] * a[1]) - (y[0] * b[0]) - (y[1] * b[1]);
    x[1] = x[0];
    x[1] = x;
    y[1] = y[0];
    y[0] = y;
    return y;
}

}} // namespace
