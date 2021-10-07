#include "model.h"

Model::~Model()
{
	// TODO: free objects, textures
	cudaFree(d_pixelsDevice);
}
// free host and device memory