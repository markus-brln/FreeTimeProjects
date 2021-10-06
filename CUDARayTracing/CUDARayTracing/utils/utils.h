#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <windows.h>						// GetModuleFileName

#include "../raytracing/triple.h"

using namespace std;


// GLOBALS
extern int SIZE_X;						// globals set in main.cc
extern int SIZE_Y;



string current_path_string_windows();
bool quadratic(double a, double b, double c, double& x0, double& x1);
double distance2D(double x1, double y1, double x2, double y2);
double distance3D(Triple t1, Triple t2);
double angle(Triple a, Triple b);
void rotateVector(Vector& vec, double x_rot, double y_rot, double z_rot);
void rotateVectorAroundVector(Vector& vec, Vector const& axis, double angle);

istream& operator>>(istream& is, Triple& t);
ostream& operator<<(ostream& os, Triple const& t);


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