#ifndef UTILS_H
#define UTILS_H

#include <filesystem>
#include <string>
#include <iostream>


using namespace std;

// GLOBALS
extern int SIZE_X;						// globals set in main.cc
extern int SIZE_Y;



string current_path_string();
//#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
//inline void gpuAssert(cudaError_t code, char* file, int line, bool abort = true)
//{
//	if (code != cudaSuccess)
//	{
//		fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
//		if (abort) exit(code);
//	}
//}
//// check for problems like too-old gpu driver version for your CUDA version
//// from https://stackoverflow.com/questions/21990904/cuda-global-function-not-called



#endif