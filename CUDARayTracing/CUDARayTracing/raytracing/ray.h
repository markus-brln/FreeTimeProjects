#ifndef RAY_H_
#define RAY_H_

#include "triple.h"

class Ray
{
public:
    Point O;        // origin
    Vector D;       // direction of the ray

    CUDA_CALLABLE_MEMBER Ray(Point const& from, Vector const& dir)
        :
        O(from),
        D(dir)
    {}

    CUDA_CALLABLE_MEMBER Point at(double t) const
    {
        Vector tmp = D;
        tmp = tmp * t;
        return O + tmp;
    }
};

#endif