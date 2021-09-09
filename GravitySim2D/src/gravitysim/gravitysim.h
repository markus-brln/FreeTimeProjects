#ifndef GRAVITYSIM_H
#define GRAVITYSIM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../utils/utils.h"

struct Star
{
    double d_x = SIZE / 2;
    double d_y = SIZE / 2;
    double d_mass = 1;
    std::vector<double> d_motion{0.0, 0.0};

    Star(double x, double y, double mass, std::vector<double> motion)
    :
        d_x(x),
        d_y(y),
        d_mass(mass),
        d_motion(motion)
    {
    }
};


class Gravitysim
{
    std::vector<Star> d_stars;

    public:
        Gravitysim();
        void timestep();
        void renderImg(sf::Image &img);

};



#endif

