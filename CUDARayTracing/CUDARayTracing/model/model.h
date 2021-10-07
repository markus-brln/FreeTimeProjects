#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include "device_launch_parameters.h"
#include "cuda_runtime.h"

#include "../utils/utils.h"
#include "../raytracing/triple.h"
#include "../raytracing/hit.h"
//#include "../raytracing/objects/object.h"
#include "../raytracing/objects/obj.h"


using namespace std;
//vector vec; 

class Model
{
	std::vector<unsigned char> d_pixelsHost;	// pixel raw data, used to initialize sf::Image
	unsigned char *d_pixelsDevice;
	//Object **d_objectsHost;						// all objects, no matter what type
	//Object **d_objectsDevice;					// GPU receives a copy
	Obj** d_d_obj = NULL;
	int n_objects;

	// CAMERA
	Point d_eye;
	Vector d_cameraDir;
	Vector d_eyeRotation;
	double d_zoom;


	public:
		Model();								// 1.cc
		
		~Model();

		void imageAlloc();
		void objectAlloc();

		unsigned char* renderImage();

		void initPixelData(int nPixels)
		{											
			//d_pixels_host = vector<unsigned char>{
			//	nPixels * 4,				// R, G, B, ALPHA -> 4
			//	allocator<unsigned char>{}  // sf::Uint8 == unsigned char -> 0-255
			//};
		}
};


#endif // !MODEL_H



