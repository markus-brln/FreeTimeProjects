#include "model.ih"


size_t mandelbrot(double real, double imag) {
	double zReal = real;
	double zImag = imag;

	for (size_t idx = 0; idx < MAX_ITER; ++idx) {
		double r2 = zReal * zReal;
		double i2 = zImag * zImag;
		
		if (r2 + i2 > 4.0) return idx;

		zImag = 2.0 * zReal * zImag + imag;
		zReal = r2 - i2 + real;
	}
	return MAX_ITER;
}


void Model::render(sf::Image &img)
{
    size_t sizeX = img.getSize().x;
    size_t sizeY = img.getSize().y;


    # pragma omp parallel for
    for (size_t y = 0; y < sizeY; ++y)
    {
        double imag = (double(y) - 0.5 * sizeY) / sizeY / 0.3 / d_zoom + d_pos.y;
        for (size_t x = 0; x < sizeY; ++x)
        {
            double real = (double(x) - 0.5 * sizeX) / sizeX / 0.3 / d_zoom + d_pos.x;
            size_t mandelValue = mandelbrot(real, imag);
            // img.setPixel(x, y, sf::Color{ static_cast<sf::Uint8>(255.0 * (1.0 - sin(0.05 * mandelValue)) / 2),  
            //                               static_cast<sf::Uint8>(255.0 * (1.0 - cos(0.3 * mandelValue)) / 2),
            //                               static_cast<sf::Uint8>(255.0 * (1.0 - cos(0.15 * mandelValue)) / 2) }); // uint8
            if (mandelValue == MAX_ITER)
                img.setPixel(x, y, sf::Color{ 0, 0, 0 });
            else
                img.setPixel(x, y, sf::Color{ static_cast<sf::Uint8>(255.0 * cos(0.02 * mandelValue) * cos(log(d_zoom))),  
                                              static_cast<sf::Uint8>(255.0 * 0),
                                              static_cast<sf::Uint8>(255.0 * 0) }); // uint8
        }        
    }
}
