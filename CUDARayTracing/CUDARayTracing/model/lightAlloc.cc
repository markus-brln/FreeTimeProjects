#include "model.h"


void Model::lightAlloc()
{
	/********************************/
	/* INITIALISE OBJ ARRAY ON HOST */
	/********************************/
	n_lights = 5;
	// Array of pointers to Objs
	Light* h_light = new Light[n_lights];
	for (size_t idx = 0; idx < n_lights; ++idx)
	{
		h_light[idx] = Light{ Point{ 0, 300, -200.0 - 500.0 * idx }, 
			Color{ double(rand() % 10) / 15, double(rand() % 10) / 15, double(rand() % 10) / 15 } };       // Create
			//Color{ 0.2, 0.3, 0.6 } };       // Create
	}

	/**************************************************/
	/* CREATE DEVICE VERSIONS AND STORE IN HOST ARRAY */
	/**************************************************/

	// Create host pointer to array-like storage of device pointers
	Light** h_d_light = (Light**)malloc(sizeof(Light*) * n_lights); //    <--------- SEE QUESTION 1
	for (size_t idx = 0; idx < n_lights; ++idx)
	{
		// Allocate space for an Light and assign
		cudaMalloc((void**)&h_d_light[idx], sizeof(Light));
		// Copy the lightect to the device (only has single scalar field to keep it simple)
		cudaMemcpy(h_d_light[idx], &h_light[idx], sizeof(Light), cudaMemcpyHostToDevice);
	}
	  
	/**************************************************/
	/* CREATE DEVICE ARRAY TO PASS POINTERS TO KERNEL */
	/**************************************************/

	// Create a pointer which will point to device memory
	d_d_lights = NULL;
	// Allocate space for 3 pointers on device at above location
	cudaMalloc((void**)&d_d_lights, sizeof(Light*) * n_lights);
	// Copy the pointers from the host memory to the device array
	cudaMemcpy(d_d_lights, h_d_light, sizeof(Light*) * n_lights, cudaMemcpyHostToDevice);


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