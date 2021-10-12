#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include "device_launch_parameters.h"
#include "cuda_runtime.h"

#include "../utils/utils.h"
#include "../raytracing/triple.h"
#include "../raytracing/hit.h"
#include "../raytracing/light.h"
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
	Light** d_d_lights = NULL;
	int n_objects;
	int n_lights;

	// CAMERA
	Point d_eye;
	Vector d_cameraDir;
	Vector d_eyeRotation;
	double d_zoom;

	// other variables
	int d_recursionDepth = 0;


	public:
		Model();								// 1.cc
		~Model();

		void imageAlloc();
		void objectAlloc();
		void lightAlloc();

		unsigned char* renderImage();

		void translateEye(double x, double y, double z)
		{
			Vector deltaEye = Vector{ x,y,z };
			rotateVector(deltaEye, d_eyeRotation.x, d_eyeRotation.y, d_eyeRotation.z);
			d_eye += deltaEye;
		}

		void rotateEye(double x, double y, double z) 
		{
			d_eyeRotation.x += x;
			d_eyeRotation.y += y;			
			d_eyeRotation.z += z;
		}


		void zoomIn(double zoom)
		{
			d_zoom *= zoom;
		}

		double getZoom()
		{
			return d_zoom;
		}

		void changeRecursionDepth(int delta)
		{
			if (d_recursionDepth + delta > -1 && d_recursionDepth + delta < 4)
			{
				d_recursionDepth += delta;
				cout << "recursion depth: " << d_recursionDepth << '\n';
			}
			else
				cout << "Recursion depth cannot be lower than 0 or higher than 2.\n";
		}
		// on my GTX 1050 a recursion depth of >3 is not possible, for GTX750M it's 2

		void initPixelData(int nPixels)
		{											
			//d_pixels_host = vector<unsigned char>{
			//	nPixels * 4,				// R, G, B, ALPHA -> 4
			//	allocator<unsigned char>{}  // sf::Uint8 == unsigned char -> 0-255
			//};
		}
};


#endif // !MODEL_H



