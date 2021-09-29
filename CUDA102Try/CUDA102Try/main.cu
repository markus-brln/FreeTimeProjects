#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <stdio.h>

using namespace std;

#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, char* file, int line, bool abort = true)
{
	if (code != cudaSuccess)
	{
		fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
		if (abort) exit(code);
	}
}


__global__ void vectorAdd(int* a, int n)
{
	int tid = (blockIdx.x * blockDim.x) + threadIdx.x;
	if (tid < n)
		a[tid] = 2;

	//for (size_t idx = 0; idx < n; ++idx)
	//	a[idx] = 2;
}


int main()
{
    cout << "hello\n";

	int n = 256;
	size_t bytes = sizeof(int) * n;

	// Allocate host memory
	int *d_a;
	int *h_a = (int*)malloc(bytes);
	gpuErrchk(cudaMalloc(&d_a, bytes));
	cudaMemcpy(d_a, h_a, bytes, cudaMemcpyHostToDevice);

	// Threadblock size
	int NUM_THREADS = 256;

	// Grid size
	int NUM_BLOCKS = (n + NUM_THREADS - 1) / NUM_THREADS;

	// Launch kernel on default stream w/o shmem
	vectorAdd << <NUM_BLOCKS, NUM_THREADS >> > (d_a, n);

	cudaMemcpy(h_a, d_a, bytes, cudaMemcpyDeviceToHost);

	for (size_t idx = 0; idx < n; ++idx)
		cout << h_a[idx];

    return 0;
}
