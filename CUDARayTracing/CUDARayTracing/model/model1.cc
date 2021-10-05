#include "model.h"


Model::Model()
{
	unsigned int pixNr = SIZE_X * SIZE_Y * 4;		
	int bytes = sizeof(unsigned char) * pixNr;

	cudaMalloc(&d_pixels_device, bytes);			// allocate image on device

	//d_pixels_host = malloc(pixnr * sizeof(unsigned char));
	d_pixels_host = vector<unsigned char>{
				pixNr,				// r, g, b, alpha -> 4
				allocator<unsigned char>{}  // sf::uint8 == unsigned char -> 0-255
	};

	//d_pixels_device;
	//initPixelData(SIZE_X * SIZE_Y);
}