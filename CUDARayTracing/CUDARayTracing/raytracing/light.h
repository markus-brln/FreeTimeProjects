#ifndef LIGHT_H_
#define LIGHT_H_

#include "triple.h"

// Declare LightPtr for use in Scene class
//#include <memory>
//class Light;
//typedef std::shared_ptr<Light> LightPtr;

class Light
{
public:
    Point position;
    Color color;

    CUDA_CALLABLE_MEMBER Light()
        :
        position(Point{ 0,0,0 }),
        color(Color{ 1,1,1 })
    {}

    CUDA_CALLABLE_MEMBER Light(Point const& pos, Color const& c)
        :
        position(pos),
        color(c)
    {}

    CUDA_CALLABLE_MEMBER Light &operator=(Light const &other)
    {
        position = other.position;
        color = other.color;

        return *this;
    }
};

#endif