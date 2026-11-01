#include <ap_int.h>
#define FIR_TAP 8
void fir_filter(ap_int<16> in, ap_int<16> &out) {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_none port=in
#pragma HLS INTERFACE ap_none port=out
#pragma HLS PIPELINE II=1
    static ap_int<16> shift_reg[FIR_TAP] = {0};
    const ap_int<16> filter_coeff[FIR_TAP] = {1,1,1,1,1,1,1,1};
#pragma HLS ARRAY_PARTITION variable=shift_reg complete dim=0
#pragma HLS ARRAY_PARTITION variable=filter_coeff complete dim=0
    ap_int<16> sum = 0;
    for(int i = FIR_TAP-1; i > 0; --i){
#pragma HLS UNROLL
        shift_reg[i] = shift_reg[i-1];
    }
    shift_reg[0] = in;
    for(int i = 0; i < FIR_TAP; ++i){
#pragma HLS UNROLL
        sum += shift_reg[i] * filter_coeff[i];
    }
    out = sum;
}