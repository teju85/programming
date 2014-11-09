#include "summation.h"


float arraySum(const vector<float>& arr) {
    vector<float>::const_iterator it;
    float sum = 0;
    if(arr.size() == 0) {
        return sum;
    }
    sum = arr[0];
    it = arr.begin();
    it++;
    if(useKahan) { // compile-time decided
        float c = 0;
        float y, t;
        for(;it!=arr.end();it++) {
            y = *it - c;
            t = sum + y;
            c = (t - sum) - y;
            sum = t;
        }
    }
    else {
        for(;it!=arr.end();it++) {
            sum += *it;
        }
    }
    return sum;
}

float arraySum(const float* arr, int size) {
    float sum = 0;
    if(size <= 0) {
        return sum;
    }
    sum = arr[0];
    if(useKahan) { // compile-time decided
        float c = 0;
        float y, t;
        for(int i=1;i<size;i++) {
            y = arr[i] - c;
            t = sum + y;
            c = (t - sum) - y;
            sum = t;
        }
    }
    else {
        for(i=1;i<size;i++) {
            sum += arr[i];
        }
    }
    return sum;
}
