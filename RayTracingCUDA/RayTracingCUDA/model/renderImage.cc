#include "model.ih"

//vector vec;

__global__ void manipulate_array(unsigned char* arr, size_t arr_size)
{
	//int tid = (blockIdx.x * blockDim.x) + threadIdx.x;	// Calculate global thread ID

	//// Boundary check
	//if (tid < arr_size)
	//{
	//	arr[tid * 4] = 100;
	//	arr[tid * 4 + 3] = 255;
	//}
}

void callFun(unsigned char* dev_dat, size_t pixelNr, int NUM_BLOCKS, int NUM_THREADS)
{
	//manipulate_array << <NUM_BLOCKS, NUM_THREADS >> > (dev_dat, pixelNr);
}


unsigned char* Model::renderImage()
{
	int pixelNr = SIZE_X * SIZE_Y;

	/*for (int idx = 0; idx < pixelNr; ++idx)
	{
		d_pixels_host[idx * 4] = 255;
		d_pixels_host[idx * 4 + 3] = 255;
	}*/


	int NUM_THREADS = 256;							// Threadblock size
	int NUM_BLOCKS = (pixelNr + NUM_THREADS - 1) / NUM_THREADS;	// Grid size


	unsigned char *host_dat = d_pixels_host.data();
	unsigned char * dev_dat;
	int bytes = sizeof(unsigned char) * pixelNr * 4;

	cudaMalloc(&dev_dat, bytes);
	cudaMemcpy(dev_dat, host_dat, bytes, cudaMemcpyHostToDevice);

	callFun(dev_dat, pixelNr, NUM_BLOCKS, NUM_THREADS);

	cudaMemcpy(host_dat, dev_dat, bytes, cudaMemcpyDeviceToHost);
	cudaDeviceSynchronize();

	return host_dat;
}