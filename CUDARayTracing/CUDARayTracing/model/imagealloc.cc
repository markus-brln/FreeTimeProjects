#include "model.h"


void Model::imageAlloc()
{
	// Image memory allocation
	unsigned int pixNr = SIZE_X * SIZE_Y * 4;
	int bytes = sizeof(unsigned char) * pixNr;
	cudaMalloc(&d_pixelsDevice, bytes);			// allocate image on device

	//d_pixels_host = malloc(pixnr * sizeof(unsigned char));
	d_pixelsHost = vector<unsigned char>{
				pixNr,				// r, g, b, alpha -> 4
				allocator<unsigned char>{}  // sf::uint8 == unsigned char -> 0-255
	};
}