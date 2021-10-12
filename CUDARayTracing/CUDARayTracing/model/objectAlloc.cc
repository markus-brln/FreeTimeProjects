#include "model.h"
#include <stdlib.h>


void Model::objectAlloc()
{
	/********************************/
	/* INITIALISE OBJ ARRAY ON HOST */
	/********************************/
	n_objects = 20;
	// Array of pointers to Objs
	Obj* h_obj = new Obj[n_objects];
	for (size_t idx = 0; idx < n_objects; ++idx)
	{
		Color sphereColor = { double(rand() % 10) / 10, double(rand() % 10) / 10, double(rand() % 10) / 10 };
		h_obj[idx] = Obj{ Point{ 100.0 * ((rand() % 10) - 5), 0, -200.0 - 200.0 * idx }, 100, sphereColor };       // Create
	}

	h_obj[0] = Obj{ Point{ 0, -1000, -1000 }, 800 };

	/**************************************************/
	/* CREATE DEVICE VERSIONS AND STORE IN HOST ARRAY */
	/**************************************************/

	// Create host pointer to array-like storage of device pointers
	Obj** h_d_obj = (Obj**)malloc(sizeof(Obj*) * n_objects); //    <--------- SEE QUESTION 1
	for (size_t idx = 0; idx < n_objects; ++idx)
	{
		// Allocate space for an Obj and assign
		cudaMalloc((void**)&h_d_obj[idx], sizeof(Obj));
		// Copy the object to the device (only has single scalar field to keep it simple)
		cudaMemcpy(h_d_obj[idx], &h_obj[idx], sizeof(Obj), cudaMemcpyHostToDevice);
	}

	/**************************************************/
	/* CREATE DEVICE ARRAY TO PASS POINTERS TO KERNEL */
	/**************************************************/

	// Create a pointer which will point to device memory
	d_d_obj = NULL;
	// Allocate space for 3 pointers on device at above location
	cudaMalloc((void**)&d_d_obj, sizeof(Obj*) * n_objects);
	// Copy the pointers from the host memory to the device array
	cudaMemcpy(d_d_obj, h_d_obj, sizeof(Obj*) * n_objects, cudaMemcpyHostToDevice);


	// Synchronise and pass back to host
	cudaDeviceSynchronize();
	//for (int i = 0; i < 3; i++) {
	//	cudaMemcpy(&h_obj[i], h_d_obj[i], sizeof(Obj), cudaMemcpyDeviceToHost);  //   <--------- SEE QUESTION 3  remove parenthesis
	//}

	//// Write out
	//for (int i = 0; i < 3; i++) {
	//	std::cout << h_obj[i].scalar << std::endl;
	//}

	//d_objectsDevice = d_d_obj;
	//d_objectsDevice = d_d_obj;


	//// Object memory allocation
	//n_objects = 1;

	///********************************/
	///* INITIALISE OBJ ARRAY ON HOST */
	///********************************/
	////Object* h_obj[1];
	//Object** h_obj = (Object**)malloc(sizeof(Object*) * n_objects);
	////Object** h_obj = new Object*[n_objects];

	//
	//for (size_t idx = 0; idx < n_objects; ++idx)
	//{
	//	h_obj[idx] = new Object{};       // Create
	//	h_obj[idx]->d_position = Point{ 0, 0, -300 };
	//	h_obj[idx]->d_radius = 100;
	//	h_obj[idx]->d_objType = Object::OBJ_TYPE::SPHERE;
	//}

	////cout << h_obj[0]->d_radius;
	////exit(0);

	///**************************************************/
	///* CREATE DEVICE VERSIONS AND STORE IN HOST ARRAY */
	///**************************************************/

	//// Create host pointer to array-like storage of device pointers
	//Object** h_d_obj = (Object**)malloc(sizeof(Object*) * n_objects);
	//for (size_t idx = 0; idx < n_objects; ++idx)
	//{
	//	// Allocate space for an Obj and assign
	//	cudaMalloc((void**)&h_d_obj[idx], sizeof(Object));
	//	// Copy the object to the device
	//	cudaMemcpy(h_d_obj[idx], &(h_obj[idx]), sizeof(Object), cudaMemcpyHostToDevice);
	//}


	////cout << host_device_obj[0]->d_radius;
	////exit(0);


	///**************************************************/
	///* CREATE DEVICE ARRAY TO PASS POINTERS TO KERNEL */
	///**************************************************/

	//// Create a pointer which will point to device memory (d_objectsDevice member)
	//Object** d_d_obj = NULL;
	//// Allocate space for 3 pointers on device at above location
	//cudaMalloc((void**)&d_d_obj, sizeof(Object*) * n_objects);
	//// Copy the pointers from the host memory to the device array
	//cudaMemcpy(d_d_obj, h_d_obj, sizeof(Object*) * n_objects, cudaMemcpyHostToDevice);

	//cudaDeviceSynchronize();

	//for (int i = 0; i < n_objects; i++) 
	//{
	//	cudaMemcpy(h_obj[i], h_d_obj[i], sizeof(Object), cudaMemcpyDeviceToHost);
	//}

	//for (int i = 0; i < n_objects; i++) 
	//{
	//	std::cout << h_obj[i]->d_position << std::endl;
	//}


	//exit(0);
	//d_objectsDevice = d_d_obj;

}