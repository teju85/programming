
void printBit(int n, int k) {
    if(n <= 0) {
        return;
    }
    if(k <= 0) {
        return;
    }
    int twoPow = 1 << k;
    if(n <= (twoPow>>1)) {
        printf("0");
        printBit(n, k-1);
    }
    else {
        printf("1");
        printBit(twoPow-n, k-1);
    }
}
