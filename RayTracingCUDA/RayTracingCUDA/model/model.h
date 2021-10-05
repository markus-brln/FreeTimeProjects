#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>

class Model
{
	std::vector<unsigned char> d_pixels_host;	// pixel raw data, used to initialize sf::Image
	//unsigned char* d_pixels_host;
	public:
		Model();								// 1.cc

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



