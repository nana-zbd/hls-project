#include "hls_stream.h"
const int N = 4;
void matrixMul(int A[N][N], int B[N][N], int C[N][N]) 
{
#pragma HLS ARRAY_PARTITION variable=A complete dim=0
#pragma HLS ARRAY_PARTITION variable=B complete dim=0
#pragma HLS ARRAY_PARTITION variable=C complete dim=0
#pragma HLS PIPELINE
for(int i=0; i<N; i++) 
{
	for(int j=0; j<N; j++) 
	{
		C[i][j] = 0;
	}
}
for(int i=0; i<N; i++) 
{
	for(int j=0; j<N; j++) 
	{
		for(int k=0; k<N; k++) 
		{
			C[i][j] += A[i][k] * B[k][j];
		}
	}
}
}
