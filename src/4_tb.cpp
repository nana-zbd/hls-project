#include <stdio.h>
#include <ap_int.h>
void vector_add(ap_int<16> A[16], ap_int<16> B[16], ap_int<16> C[16]);
int main()
{
	ap_int<16> A[16], B[16], C[16], golden[16];
	for(int i = 0; i < 16; ++i) {
		A[i] = i % 256;
		B[i] = 128 + i % 128;
		golden[i] = A[i] + B[i];
	}
	vector_add(A, B, C);
	for(int i = 0; i < 16; ++i) {
		if(C[i] != golden[i]) {
			printf("Testbench failed at index: %d\n", i);
			printf("Expected: %d Got: %d\n", (int)golden[i], (int)C[i]);
			return -1;
		}
	}
	printf("All tests passed!\n");
	return 0;
}