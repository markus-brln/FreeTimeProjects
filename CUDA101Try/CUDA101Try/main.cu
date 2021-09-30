#include "cuda_runtime.h"
//#include "device_launch_parameters.h"
#include <iostream>
#include <vector>
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
// check for problems like too-old gpu driver version for your CUDA version
// from https://stackoverflow.com/questions/21990904/cuda-global-function-not-called


__device__ void hello_device()
{
	printf("hello from device-only function\n");
}


__global__ void call_device_function()
{
	hello_device();
}


__global__ void print_hello_device()
{
	printf("hello from device global function\n");
}

class GPU_Embassador
{
	int i;
	
	public:
		__device__ __host__ void assignValue(int val)
		{
			i = val;
		}

		__device__ __host__ int getValue()
		{
			return i;
		}
};

__global__ void manipulate_array(int* arr, size_t arr_size)
{
	int tid = (blockIdx.x * blockDim.x) + threadIdx.x;	// Calculate global thread ID

	// Boundary check
	if (tid < arr_size) 
		arr[tid] += 2;
}

__global__ void manipulate_class_obj(GPU_Embassador *obj)
{
	obj->assignValue(20);
}

void try_cudaMallocManaged()
{
	GPU_Embassador obj;
	obj.assignValue(10);
	GPU_Embassador* device_obj;
	cudaMallocManaged(&device_obj, sizeof(GPU_Embassador));
	*device_obj = obj;
	manipulate_class_obj << <1, 1 >> > (device_obj);
	cudaDeviceSynchronize();
	cout << "obj's data member changed? " << device_obj->getValue() << '\n';
}

void try_manipulate_std_vector()
{
	int vec_size = 1000;

	int NUM_THREADS = 256;							// Threadblock size
	int NUM_BLOCKS = (vec_size + NUM_THREADS - 1) / NUM_THREADS;	// Grid size

	vector<int> vec{ vec_size, 1 };
	cout << vec.size(); 

	int *host_dat = vec.data();
	int* dev_dat;
	int bytes = sizeof(int) * vec.size();
	cudaMalloc(&dev_dat, bytes);
	cudaMemcpy(dev_dat, host_dat, bytes, cudaMemcpyHostToDevice);

	manipulate_array << <NUM_BLOCKS, NUM_THREADS >> > (dev_dat, vec.size());

	cudaMemcpy(host_dat, dev_dat, bytes, cudaMemcpyDeviceToHost);
	cudaDeviceSynchronize();

	cout << vec.size();
	//for (auto elem : vec)
		//cout << elem;
}


int main()
{
	try_manipulate_std_vector();

	exit(0);

	cout << "hello from host\n";
	print_hello_device << <1, 1 >> > ();
	call_device_function << <1, 1 >> > ();
	cudaDeviceSynchronize();

	size_t n = 1 << 20;
	cout << "n: " << n << '\n';

	size_t bytes = sizeof(int) * n;
	int *h_a = (int*)malloc(bytes);					// Allocate host memory

	for (size_t idx = 0; idx < n; ++idx)
		h_a[idx] = 1;

	int* d_a;										// allocate device memory,
	gpuErrchk(cudaMalloc(&d_a, bytes));				// check whether gpu driver version is ok etc
	cudaMemcpy(d_a, h_a, bytes, cudaMemcpyHostToDevice);

	
	int NUM_THREADS = 256;							// Threadblock size
	int NUM_BLOCKS = (n + NUM_THREADS - 1) / NUM_THREADS;	// Grid size

	for (size_t idx = 0; idx < 1000; ++idx)
	{
		manipulate_array << <NUM_BLOCKS, NUM_THREADS >> > (d_a, n);
		cudaDeviceSynchronize();					// stop host code from doing stupid things
	}

	cudaMemcpy(h_a, d_a, bytes, cudaMemcpyDeviceToHost);


	for (size_t idx = 0; idx < 100; ++idx)			// check whether device actually did something
		cout << h_a[idx];



    return 0;
}
