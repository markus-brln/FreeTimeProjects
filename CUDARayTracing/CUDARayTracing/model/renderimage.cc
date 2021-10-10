#include "model.h"
#include "../raytracing/tracing.h"
 


__global__ void traceKernel(unsigned char* arr, size_t arr_size, Point screenCentre,
	Point eye, Vector down, Vector right, int size_x, int size_y, Obj **d_d_obj, int n_objects,
	Light** lights, int n_lights, int recursionDepth)
{
	//printf("%d\n", n_objects);
	//printf("screencenter %f %f %f\n down %f %f %f\n right %f %f %f\n", 
	//	screenCentre.x, screenCentre.y, screenCentre.z,
	//	down.x, down.y, down.z,
	//	right.x, right.y, right.z);
	//printf("right %f %f %f\n", screenCentre.x, screenCentre.y, screenCentre.z);
	int tid = (blockIdx.x * blockDim.x) + threadIdx.x;	// calculate global thread id

	//printf("hello\n");
	//printf("scalar %f %f %f %f\n", d_d_obj[0]->d_position.z, d_d_obj[1]->d_position.z, d_d_obj[2]->d_position.z, d_d_obj[2]->d_radius);

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
	 
	 
	// boundary check
	if (tid < arr_size)
	{
		double x_coordinate = tid % size_x;
		double y_coordinate = tid / size_y;
		  
		//printf("coords %f %f\n", x_coordinate, y_coordinate);
		 
		//if (y_coordinate < 50)
		//	printf("%d %d\n", x_coordinate, y_coordinate);
		// go from top left to bottom right, using the 3 rotated vectors
		Point pixel = screenCentre + right * (x_coordinate - size_x / 2) + down * (y_coordinate - size_y / 2);
		//printf("%f %f %f\n", pixel.x, pixel.y, pixel.z);
		Ray ray(eye, (pixel - eye).normalized());   // shoot ray through pixel
		//printf("%f %f %f\n", ray.D.x, ray.D.y, ray.D.z);
		Color col = trace(ray, recursionDepth, d_d_obj, n_objects, lights, n_lights);					// recursion depth == 1 
		//Color col{ 1, 1, 1 };
		col.clamp();                                // some spots might be too bright
		arr[tid * 4] = int(col.r * 255);
		arr[tid * 4 + 1] = int(col.g * 255);
		arr[tid * 4 + 2] = int(col.b * 255);
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
	 
	//cout << down << right << d_camera << screenCentre << d_eye << d_eyeRotation << d_zoom << '\n';
  
	traceKernel << <NUM_BLOCKS, NUM_THREADS >> > (d_pixelsDevice, pixelNr, screenCentre, 
		d_eye, down, right, SIZE_X, SIZE_Y, d_d_obj, n_objects, d_d_lights, n_lights, d_recursionDepth);
	 

	cudaMemcpy(d_pixelsHost.data(), d_pixelsDevice, bytes, cudaMemcpyDeviceToHost);
	cudaDeviceSynchronize();

	return d_pixelsHost.data();
}