#include "model.h"

Model::~Model()
{
	cudaFree(d_pixels_device);
}
// free host and device memory