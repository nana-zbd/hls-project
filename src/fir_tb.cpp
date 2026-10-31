#include <stdio.h>
#include "fir.h"

int main() {
    data_t x;
    data_t y;
    int i;
    
    for (i = 0; i < 20; i++) {
        x = i * 2;
        fir(&y, x);
        printf("Input: %d, Output: %d\n", x, y);
    }
    return 0;
}