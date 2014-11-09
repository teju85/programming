#include <stdio.h>
#include <vector>
using namespace std;

#define CHECK(expected, arr) do {                                    \
    int val = fill(arr, sizeof(arr) / sizeof(int));             \
    if(val != expected) {                                            \
        printf("FAIL! Line=%d Arr='%s'! Expected=%d obtained=%d\n",  \
               __LINE__, #arr, expected, val);                       \
    }                                                                \
    else {                                                           \
        printf(" PASS Line=%d Arr='%s'\n", __LINE__, #arr);          \
    }                                                                \
} while(0)

int fill(const int* land, int size) {
    int leftMax = 0;
    int rightMax = 0;
    int left = 0;
    int right = size - 1;
    int volume = 0;
    while(left < right) {
        if(land[left] > leftMax) {
            leftMax = land[left];
        }
        if(land[right] > rightMax) {
            rightMax = land[right];
        }
        if(leftMax >= rightMax) {
            volume += rightMax - land[right];
            right--;
        }
        else {
            volume += leftMax - land[left];
            left++;
        }
    }
    return volume;
}

int main(int argc, char** argv) {
    const int arr1[] = {2, 2, 2, 2, 2, 2};
    CHECK(0, arr1);
    const int arr2[] = {1, 2, 3, 4, 5};
    CHECK(0, arr2);
    const int arr3[] = {5, 4, 3, 2, 1};
    CHECK(0, arr3);
    const int arr4[] = {5, 4, 3, 2, 1, 5};
    CHECK(10, arr4);
    const int arr5[] = {5, 1, 2, 4, 3, 4};
    CHECK(6, arr5);
    const int arr6[] = {2, 5, 1, 2, 3, 4, 7, 7, 6};
    CHECK(10, arr6);
    const int arr7[] = {2, 7, 2, 7, 4, 7, 1, 7, 3, 7};
    CHECK(18, arr7);
    const int arr8[] = {2, 10, 2, 6, 4, 11, 1, 7, 3, 7};
    CHECK(28, arr8);
    const int arr9[] = {2, 10, 2, 6, 13, 11, 1, 7, 3, 7};
    CHECK(22, arr9);
    const int arr10[] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};
    CHECK(0, arr10);
    return 0;
}
