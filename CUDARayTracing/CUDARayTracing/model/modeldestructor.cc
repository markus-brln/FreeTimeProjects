#include "model.h"

Model::~Model()
{
	cudaFree(d_pixelsDevice);
}
// free host and device memory