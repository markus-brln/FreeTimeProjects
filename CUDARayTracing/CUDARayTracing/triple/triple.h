#ifndef TRIPLE_H
#define TRIPLE_H


#ifdef __CUDACC__
#define CUDA_CALLABLE_MEMBER __host__ __device__
#else
#define CUDA_CALLABLE_MEMBER
#endif // https://stackoverflow.com/questions/6978643/cuda-and-classes

#include <math.h>



// Color, Point and Vector are all Triples (name them so)
class Triple;
typedef Triple Color;
typedef Triple Point;
typedef Triple Vector;

class Triple
{
    public:
        // union to acces the same elements by
        // x, y, z, or r, g, b or data[index]
        union {
            double data[3];
            struct {
                double x;
                double y;
                double z;
            };
            struct {
                double r;
                double g;
                double b;
            };
        };

        CUDA_CALLABLE_MEMBER Triple(double X = 0, double Y = 0, double Z = 0)
        :
            x(X),
            y(Y),
            z(Z)
        {}
};


#endif // !TRIPLE_H