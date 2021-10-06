#include "model.h"
#include "../raytracing/tracing.h"
#include <vector>


__global__ void manipulate_array(unsigned char* arr, size_t arr_size, Point screenCentre, 
	Point eye, Vector down, Vector right, size_t size_x, size_t size_y, Object **objects, size_t n_objects)
{
	int tid = (blockIdx.x * blockDim.x) + threadIdx.x;	// calculate global thread id

	/*Color col{ 4.0, 4.0, 4.0 };
	Color col2{ 2, 2, 2 };
	Color col3 = col + col2;

	col3 = col3 * col2;

	col3 *= 3;
	col3.normalize();
	Triple t = col + col * 3;
	Triple t1 = t.reflect(col);

	Sphere s1{ Point{}, 20 };
	Hit h1 = Hit::NO_HIT();
	Ray r1 = Ray{ Point{0, 0, 0}, Vector{1, 0, 0} };*/
	//printf("%f ", t1.x);


	
	
	// 
	// boundary check
	if (tid < arr_size)
	{
		int x_coordinate = tid % size_x;
		int y_coordinate = tid / size_y;

		//if (y_coordinate < 50)
		//	printf("%d %d\n", x_coordinate, y_coordinate);
		// go from top left to bottom right, using the 3 rotated vectors
		Point pixel = screenCentre + right * (x_coordinate - size_x / 2) + down * (y_coordinate - size_y / 2);

		Ray ray(eye, (pixel - eye).normalized());   // shoot ray through pixel
		Color col = trace(ray, 1, objects, n_objects);					// recursion depth == 1
		//col.clamp();                                // some spots might be too bright
		arr[tid * 4] = 100;
		arr[tid * 4 + 3] = 255;
	}
}


unsigned char* Model::renderImage()
{
	int pixelNr = SIZE_X * SIZE_Y;

	int NUM_THREADS = 256;							// Threadblock size
	int NUM_BLOCKS = (pixelNr + NUM_THREADS - 1) / NUM_THREADS;	// Grid size
	int bytes = sizeof(unsigned char) * pixelNr * 4;	// n_bytes of image

	Vector down{ 0, -1, 0 };            // vector down from centre of screen
	Vector right{ 1, 0, 0 };            // vector right from centre

										// no Z-rotation yet
	rotateVector(down, d_eyeRotation.x, d_eyeRotation.y, 0);
	rotateVector(right, d_eyeRotation.x, d_eyeRotation.y, 0);

	// camera perpendicular to screen formed
	Vector d_camera = right.cross(down);// by right+down

	// rotate around the camera for Z-rotation (unfinished)
	// rotateVectorAroundVector(down, d_camera, eyeRotation.z);
	// rotateVectorAroundVector(right, d_camera, eyeRotation.z);

	Point screenCentre = d_eye + d_camera * SIZE_X * d_zoom;

	manipulate_array << <NUM_BLOCKS, NUM_THREADS >> > (d_pixelsDevice, pixelNr, screenCentre, 
		d_eye, down, right, SIZE_X, SIZE_Y, d_objectsDevice, n_objects);
	//::callFun<<<1, 1>>>(dev_dat, pixelNr, NUM_BLOCKS, NUM_THREADS);

	cudaMemcpy(d_pixelsHost.data(), d_pixelsDevice, bytes, cudaMemcpyDeviceToHost);
	cudaDeviceSynchronize();

	return d_pixelsHost.data();
}