#ifndef OBJECT_H
#define OBJECT_H

#include "../triple.h"
#include "../ray.h"
#include "../hit.h"
#include "../../utils/utils.h"


class Object
{
	public:
        enum OBJ_TYPE
        {
            SPHERE = 0,
            TRIANGLE = 1
        };
        size_t d_objType;
		// Material data members
        Color color;        // base color
        double ka;          // ambient intensity
        double kd;          // diffuse intensity
        double ks;          // specular intensity
        double n;           // exponent for specular highlight size

        bool hasTexture = false;
        unsigned char* texture;

        bool isTransparent = false;
        double nt = 1.0;

        // Sphere data members
        Point d_position;
        double const d_radius;
        Vector const d_axis;
        double const d_angle;

        CUDA_CALLABLE_MEMBER Object(Point const& spherePos, double SphereRadius,
            Vector const& SphereAxis = Vector(0.0, 1.0, 0.0), double SphereAngle = 0.0)
            :
            d_position(spherePos),
            d_radius(SphereRadius),
            d_axis(SphereAxis),
            d_angle(SphereAngle),
            d_objType(OBJ_TYPE::SPHERE)
        {
            //this->d_position = pos;
        }

        CUDA_CALLABLE_MEMBER Hit intersect(Ray const& ray)
        {
            switch (d_objType)
            {
            case (OBJ_TYPE::SPHERE):
                return intersectSphere(ray);
            case (OBJ_TYPE::TRIANGLE):
                break;
            default:
                break;
            }
        }

        CUDA_CALLABLE_MEMBER Hit intersectSphere(Ray const& ray)
        {
            // Sphere formula: ||x - position||^2 = r^2
            // Line formula:   x = ray.O + t * ray.D

            Vector L = ray.O - d_position;
            double a = ray.D.dot(ray.D);
            double b = 2.0 * ray.D.dot(L);
            double c = L.dot(L) - d_radius * d_radius;

            double t0;
            double t1;

            bool quadratic_solved = quadratic(a, b, c, t0, t1);
            if (!quadratic_solved)
            {
                Hit no_hit{ 0, Vector{} , NULL };
                no_hit.hit = false;
                return no_hit;
                //return Hit::NO_HIT();
            }

            // t0 is closest hit
            if (t0 < 0.0)  // check if it is not behind the camera
            {
                t0 = t1;    // try t1
                if (t0 < 0.0) // both behind the camera
                {
                    Hit no_hit{ 0, Vector{} , NULL };
                    no_hit.hit = false;
                    return no_hit;
                    //return Hit::NO_HIT();
                }
            }

            // calculate normal
            Point hit = ray.at(t0);
            Vector N = (hit - d_position).normalized();

            // Note that the direction of the normal is not changed here,
            // but in scene.cpp - if necessary.

            return Hit(t0, N, this);
        }

        // no virtual functions allowed for CUDA... just implemented in each 
        // specific object
        //virtual ~Object() = default;
        //virtual Hit intersect(Ray const& ray) = 0;
        //virtual Vector toUV(Point const& hit);

};


#endif // !OBJECT_H