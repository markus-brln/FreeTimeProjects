#include "gravitysim.ih"

void Gravitysim3D::renderImg(Image &img)
{
    for (Star star : d_stars)
    {
        if (star.d_x > 0 && star.d_x < SIZE && star.d_y > 0 && star.d_y < SIZE)
            img.setPixel(star.d_x, star.d_y, sf::Color(255, 255, 255));
    }
    
}