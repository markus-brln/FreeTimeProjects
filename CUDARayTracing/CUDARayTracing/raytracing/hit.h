#ifndef HIT_H_
#define HIT_H_

#include "triple.h"
//#include "objects/object.h"

class Hit
{
    public:
        double t;   // distance of hit
        Vector N;   // Normal at hit
        void *hitObj;
        bool hit;   // MB signify whether any object was actually hit

        CUDA_CALLABLE_MEMBER Hit(double time, Vector const& normal, void *hitObj)
            :
            t(time),
            N(normal),
            hit(true),
            hitObj(hitObj)
        {}

        CUDA_CALLABLE_MEMBER static Hit const NO_HIT()
        {
            Hit no_hit{ 100000, Vector{} , NULL};
            no_hit.hit = false;
            /*static Hit no_hit(std::numeric_limits<double>::quiet_NaN(),
                Vector(std::numeric_limits<double>::quiet_NaN(),
                    std::numeric_limits<double>::quiet_NaN(),
                    std::numeric_limits<double>::quiet_NaN()));*/
            return no_hit;
        }
};

#endif