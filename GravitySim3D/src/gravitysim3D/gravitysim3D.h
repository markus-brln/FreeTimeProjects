#ifndef GRAVITYSIM_H
#define GRAVITYSIM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../utils/utils.h"

struct Star
{
    Point d_pos;
    Vector d_motion;
    double d_mass;
    
    Star(Point pos, Vector motion, double mass)
    :
        d_pos(pos),
        d_motion(motion),
        d_mass(mass)
    {
    }
};


class Gravitysim3D
{
    std::vector<Star> d_stars;

    public:
        Gravitysim3D();

        void resetStars();
        void timestep();
        void renderImg(sf::Image &img);

        std::vector<Star> &stars() { return d_stars; }
        void setStars(std::vector<Star> &newStars) { d_stars = newStars; }
};



#endif

