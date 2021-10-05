#include <cuda_runtime.h>
#include <iostream>
#include <stdio.h>
#include "myclass/myclass.h"

__global__ void print_hello_global()
{
	printf("hello from device global function\n");
}



int main()
{
	print_hello_global << <2, 2 >> > ();

	cudaDeviceSynchronize();

	MyClass myclass_obj;

	myclass_obj.call_global();

	return 0;
}