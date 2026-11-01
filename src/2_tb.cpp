#include <stdio.h>
#include <ap_int.h>
#define TAP 8
#define DATA_WIDTH 16
void fir_filter(ap_int<16> in, ap_int<16> &out);
int main() {
    ap_int<DATA_WIDTH> in_seq[16];
    ap_int<DATA_WIDTH> golden[16] = {0};
    for(int i = 0; i < 16; i++){
        in_seq[i] = i % 256;
    }
    for(int i = 0; i < 16; i++){
        ap_int<DATA_WIDTH> sum = 0;
        for(int k = 0; k < TAP; k++){
            if(i - k >= 0) sum += in_seq[i - k];
        }
        golden[i] = sum;
    }
    ap_int<DATA_WIDTH> out_data;
    for(int i = 0; i < 16; i++){
        fir_filter(in_seq[i], out_data);
        if(out_data != golden[i]){
            printf("Test failed at index %d, expected: %d, got: %d\n", i, (int)golden[i], (int)out_data);
            return -1;
        }
    }
    printf("All tests passed!\n");
    return 0;
}