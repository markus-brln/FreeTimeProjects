#include "model.h"


__global__ void manipulate_array(unsigned char* arr, size_t arr_size)
{
	int tid = (blockIdx.x * blockDim.x) + threadIdx.x;	// calculate global thread id

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

	/*for (int idx = 0; idx < pixelNr; ++idx)
	{
		d_pixels_host[idx * 4] = 255;
		d_pixels_host[idx * 4 + 3] = 255;
	}*/


	int NUM_THREADS = 1024;							// Threadblock size
	int NUM_BLOCKS = (pixelNr + NUM_THREADS - 1) / NUM_THREADS;	// Grid size


	unsigned char* host_dat = d_pixels_host.data();
	unsigned char* dev_dat;
	int bytes = sizeof(unsigned char) * pixelNr * 4;

	cudaMalloc(&dev_dat, bytes);
	cudaMemcpy(dev_dat, host_dat, bytes, cudaMemcpyHostToDevice);

	manipulate_array << <NUM_BLOCKS, NUM_THREADS >> > (dev_dat, pixelNr);
	//::callFun<<<1, 1>>>(dev_dat, pixelNr, NUM_BLOCKS, NUM_THREADS);

	cudaMemcpy(host_dat, dev_dat, bytes, cudaMemcpyDeviceToHost);
	cudaDeviceSynchronize();

	return host_dat;
}