#include <ap_int.h>
void vector_sum(ap_int<32> data[32], ap_int<32> &sum) {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE s_axilite port=data
#pragma HLS INTERFACE ap_none port=sum
#pragma HLS PIPELINE II=1
	ap_int<32> s = 0;
	for(int i = 0; i < 32; ++i) {
		#pragma HLS UNROLL
		s += data[i];
	}
	sum = s;
}