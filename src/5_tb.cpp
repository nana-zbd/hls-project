#include <stdio.h>
#include <ap_int.h>
void vector_sum(ap_int<32> data[32], ap_int<32> &sum);
int main() {
	ap_int<32> data[32], out_sum;
	ap_int<32> golden = 0;
	for(int i = 0; i < 32; ++i) {
		data[i] = i % 256;
		golden += data[i];
	}
	vector_sum(data, out_sum);
	if(out_sum != golden) {
		printf("Testbench failed!\n");
		printf("Expected: %d Got: %d\n", (int)golden, (int)out_sum);
		return -1;
	}
	printf("All tests passed!\n");
	return 0;
}