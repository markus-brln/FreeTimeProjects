#include <iostream>
#include "cuda_runtime.h"

class Obj {

public:
    int scalar;
    __host__ __device__
        void changeToFive() { scalar = 5; }
};

// Kernel
__global__ void myKernel(Obj** d_array_of_objs)
{
    // Change the scalar of each object to 5
    // by dereferencing device array to get
    // appropriate object pointer.
    int idx = threadIdx.x + blockDim.x * blockIdx.x;
    // (*d_array_of_objs)->changeToFive();  //  <--------- SEE QUESTION 4 (add parenthesis)
    d_array_of_objs[idx]->changeToFive();
}

void makeObjects()
{
    /********************************/
    /* INITIALISE OBJ ARRAY ON HOST */
    /********************************/

    // Array of 3 pointers to Objs
    Obj* h_obj[3];
    for (int i = 0; i < 3; i++) {
        h_obj[i] = new Obj();       // Create
        h_obj[i]->scalar = i * 10;  // Initialise
    }

    // Write out
    for (int i = 0; i < 3; i++) {
        std::cout << h_obj[i]->scalar << std::endl;
    }


    /**************************************************/
    /* CREATE DEVICE VERSIONS AND STORE IN HOST ARRAY */
    /**************************************************/

    // Create host pointer to array-like storage of device pointers
    Obj** h_d_obj = (Obj**)malloc(sizeof(Obj*) * 3); //    <--------- SEE QUESTION 1
    for (int i = 0; i < 3; i++) {
        // Allocate space for an Obj and assign
        cudaMalloc((void**)&h_d_obj[i], sizeof(Obj));
        // Copy the object to the device (only has single scalar field to keep it simple)
        cudaMemcpy(h_d_obj[i], &(h_obj[i]), sizeof(Obj), cudaMemcpyHostToDevice);
    }

    /**************************************************/
    /* CREATE DEVICE ARRAY TO PASS POINTERS TO KERNEL */
    /**************************************************/

    // Create a pointer which will point to device memory
    Obj** d_d_obj = NULL;
    // Allocate space for 3 pointers on device at above location
    cudaMalloc((void**)&d_d_obj, sizeof(Obj*) * 3);
    // Copy the pointers from the host memory to the device array
    cudaMemcpy(d_d_obj, h_d_obj, sizeof(Obj*) * 3, cudaMemcpyHostToDevice);
}

// Entry point
int main()
{

    /********************************/
    /* INITIALISE OBJ ARRAY ON HOST */
    /********************************/

    // Array of 3 pointers to Objs
    Obj* h_obj[3];
    for (int i = 0; i < 3; i++) {
        h_obj[i] = new Obj();       // Create
        h_obj[i]->scalar = i * 10;  // Initialise
    }

    // Write out
    for (int i = 0; i < 3; i++) {
        std::cout << h_obj[i]->scalar << std::endl;
    }


    /**************************************************/
    /* CREATE DEVICE VERSIONS AND STORE IN HOST ARRAY */
    /**************************************************/

    // Create host pointer to array-like storage of device pointers
    Obj** h_d_obj = (Obj**)malloc(sizeof(Obj*) * 3); //    <--------- SEE QUESTION 1
    for (int i = 0; i < 3; i++) {
        // Allocate space for an Obj and assign
        cudaMalloc((void**)&h_d_obj[i], sizeof(Obj));
        // Copy the object to the device (only has single scalar field to keep it simple)
        cudaMemcpy(h_d_obj[i], &(h_obj[i]), sizeof(Obj), cudaMemcpyHostToDevice);
    }

    /**************************************************/
    /* CREATE DEVICE ARRAY TO PASS POINTERS TO KERNEL */
    /**************************************************/

    // Create a pointer which will point to device memory
    Obj** d_d_obj = NULL;
    // Allocate space for 3 pointers on device at above location
    cudaMalloc((void**)&d_d_obj, sizeof(Obj*) * 3);
    // Copy the pointers from the host memory to the device array
    cudaMemcpy(d_d_obj, h_d_obj, sizeof(Obj*) * 3, cudaMemcpyHostToDevice);


    /**********
     * After the above, VS2013 shows the memory pointed to by d_d_obj
     * to be NULL <------- SEE QUESTION 2.
     **********/


     // Launch Kernel
    myKernel << <1, 3 >> > (d_d_obj);

    // Synchronise and pass back to host
    cudaDeviceSynchronize();
    for (int i = 0; i < 3; i++) {
        cudaMemcpy(h_obj[i], h_d_obj[i], sizeof(Obj), cudaMemcpyDeviceToHost);  //   <--------- SEE QUESTION 3  remove parenthesis
    }

    // Write out
    for (int i = 0; i < 3; i++) {
        std::cout << h_obj[i]->scalar << std::endl;
    }

    return 0;
}