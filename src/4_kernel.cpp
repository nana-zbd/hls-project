#include <ap_int.h>
void vector_add(ap_int<16> A[16], ap_int<16> B[16], ap_int<16> C[16])
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE s_axilite port=A
#pragma HLS INTERFACE s_axilite port=B
#pragma HLS INTERFACE s_axilite port=C
#pragma HLS PIPELINE II=1
	for(int i = 0; i < 16; ++i)
	{
		#pragma HLS UNROLL
		C[i] = A[i] + B[i];
	}
}