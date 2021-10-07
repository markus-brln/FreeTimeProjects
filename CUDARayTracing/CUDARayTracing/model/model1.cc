#include "model.h"


Model::Model()
	:
	d_eye(Point{ 0, 0, 0 }),
	d_cameraDir(Vector{ 0, 0, -1 }),
	d_eyeRotation(Vector{ 0, 0, 0 }),
	d_zoom(1.0)
{
	imageAlloc();						// allocate memory on GPU
	objectAlloc();
}


/*
	//Object** hostObjects = new Object*[n_objects];
	Object* hostObjects[1];



	Object** deviceObjects;
	cudaMalloc(&deviceObjects, sizeof(Object*) * n_objects);

	printf("%d %d", sizeof(deviceObjects), sizeof(deviceObjects[0]));

	for (size_t idx = 0; idx < n_objects; ++idx)
	{
		Object* tmp;
		cudaMalloc(&tmp, sizeof(Object));
		tmp = new Object{ Point{0, 0, -200}, 100 };
		deviceObjects[0] = tmp;//new Object{ Point{0, 0, -200}, 100 };
		//cudaMemcpy(tmpDevice, d_objectsHost[idx], sizeof(*d_objectsHost[idx]), cudaMemcpyHostToDevice);
		//d_objectsDevice[idx] = tmpDevice;
	}
	//Object sphere1{ Point{0, 0, -200}, 100 };
	//new(&amp;other.u_word) string{ std::move(u_word) };
	//d_objectsHost.push_back(new Object{ Point{0, 0, -200}, 100 });

	//d_objectsHost = new Object*[n_objects];			// model stores pointer addresses of objects
	//Object* pointerToFirstObj = d_objectsHost[0];
	//printf("%ld", d_objectsHost.size());

	//pointerToFirstObj = new Object{ Point{0, 0, -200}, 100 };

	//cudaMalloc(&d_objectsDevice, n_objects * sizeof(Object*));
	//d_objectsDevice = NULL;

	//Object sth = Object{ *d_objectsHost[0] };
	//printf("%d", sizeof(d_objectsDevice));
	//exit(0);

	//cout << d_objectsDevice << " " << d_objectsDevice;
	exit(0);


	//for (size_t idx = 0; idx < n_objects; ++idx)
	//{
	//	Object* tmpDevice;
	//	printf("size obj %d\n", sizeof(*d_objectsHost[idx]));
	//	cudaMalloc(&tmpDevice, sizeof(Object*));
	//	tmpDevice = new Object{ Point{0, 0, -200}, 100 };
	//	//cudaMemcpy(tmpDevice, d_objectsHost[idx], sizeof(*d_objectsHost[idx]), cudaMemcpyHostToDevice);
	//	//d_objectsDevice[idx] = tmpDevice;
	//}
	//exit(0);

	//d_pixels_device;
	//initPixelData(SIZE_X * SIZE_Y);*/