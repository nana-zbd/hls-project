#include <stdio.h>
const int N = 4;
void matrixMul(int A[N][N], int B[N][N], int C[N][N]);
int main() 
{
	const int N = 4;
	int A[N][N], B[N][N], C_ref[N][N], C[N][N];
	for(int i=0; i<N; i++) 
	{
		for(int j=0; j<N; j++) 
		{
			A[i][j] = i + j;
			B[i][j] = i * j;
		}
	}
	for(int i=0; i<N; i++) 
	{
		for(int j=0; j<N; j++) 
		{
			C_ref[i][j] = 0;
		}
	}
	for(int i=0; i<N; i++) 
	{
		for(int j=0; j<N; j++) 
		{
			for(int k=0; k<N; k++) 
			{
				C_ref[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	matrixMul(A, B, C);
	bool isCorrect = true;
	for(int i=0; i<N; i++) 
	{
		for(int j=0; j<N; j++) 
		{
			if(C[i][j] != C_ref[i][j]) 
			{
				isCorrect = false;
				break;
			}
		}
	}
	if (isCorrect) { printf("Result OK\n"); } else { printf("Result Error\n"); }
	return 0;
}