#include "model.h"
#include <vector>


__global__ void manipulate_array(unsigned char* arr, size_t arr_size)
{
	int tid = (blockIdx.x * blockDim.x) + threadIdx.x;	// calculate global thread id

	Color col{ 0.0, 0.0, 0.0 };


	// boundary check
	if (tid < arr_size)
	{
		arr[tid * 4] = 100;
		arr[tid * 4 + 3] = 255;
	}
}


unsigned char* Model::renderImage()
{
	int pixelNr = SIZE_X * SIZE_Y;

	int NUM_THREADS = 256;							// Threadblock size
	int NUM_BLOCKS = (pixelNr + NUM_THREADS - 1) / NUM_THREADS;	// Grid size


	unsigned char* host_dat = d_pixels_host.data();
	//unsigned char* dev_dat;
	int bytes = sizeof(unsigned char) * pixelNr * 4;

	//cudaMalloc(&dev_dat, bytes);
	//cudaMemcpy(dev_dat, host_dat, bytes, cudaMemcpyHostToDevice);

	manipulate_array << <NUM_BLOCKS, NUM_THREADS >> > (d_pixels_device, pixelNr);
	//::callFun<<<1, 1>>>(dev_dat, pixelNr, NUM_BLOCKS, NUM_THREADS);

	cudaMemcpy(host_dat, d_pixels_device, bytes, cudaMemcpyDeviceToHost);
	cudaDeviceSynchronize();

	return host_dat;
}