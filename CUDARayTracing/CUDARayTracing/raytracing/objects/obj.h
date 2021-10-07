#ifndef OBJ_H
#define OBJ_H

#include "cuda_runtime.h"
#include "../ray.h"

class Obj
{

    public:
        enum OBJ_TYPE
        {
            NONE = 0,
            SPHERE = 1,
            TRIANGLE = 2
        };
        int d_objType;

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
        double d_radius;
        Vector d_axis;
        double d_angle;

        CUDA_CALLABLE_MEMBER Obj()
        {
        }


        CUDA_CALLABLE_MEMBER Obj(Point const& spherePos, double SphereRadius,
            Vector const& SphereAxis = Vector(0.0, 1.0, 0.0), double SphereAngle = 0.0)
            :
            d_position(spherePos),
            d_radius(SphereRadius),
            d_axis(SphereAxis),
            d_angle(SphereAngle),
            d_objType(OBJ_TYPE::SPHERE)
        {
        }

        CUDA_CALLABLE_MEMBER Hit intersect(Ray const& ray)
        {
            //printf("d_objType %d\n", d_objType);
            switch (d_objType)
            {
            case (OBJ_TYPE::SPHERE):
                return intersectSphere(ray);
            case (OBJ_TYPE::TRIANGLE):
                break;
            default:
                break;
            }
            return Hit::NO_HIT();
        }

        CUDA_CALLABLE_MEMBER bool quadratic(double a, double b, double c,
            double& x0, double& x1)
        {
            //printf("hello quad\n");
            double discr = b * b - 4.0 * a * c;

            if (discr < 0.0)
                return false;   // no solution

            if (discr == 0.0)
            {
                x0 = x1 = -0.5 * b / a;
            }
            else
            {
                double q = (b > 0.0) ?
                    -0.5 * (b + sqrt(discr)) :
                    -0.5 * (b - sqrt(discr));
                x0 = q / a;
                x1 = c / q;
            }

            if (x0 > x1)
            {
                double h = x0;
                h = x0;
                x0 = x1;
                x1 = h;
                //std::swap(x0, x1);
            }

            return true;
        }


        CUDA_CALLABLE_MEMBER Hit intersectSphere(Ray const& ray)
        {
            // Sphere formula: ||x - position||^2 = r^2
            // Line formula:   x = ray.O + t * ray.D
           /*printf("pos %f %f %f ray.O %f %f %f, ray.D %f %f %f\n",
                d_position.x, d_position.y, d_position.z,
                ray.O.x, ray.O.y, ray.O.z,
                ray.D.x, ray.D.y, ray.D.z);*/
           // pos 0.0 0.0 -200.0 
           // ray.O 0.0 0.0 0.0
           // ray.D 0.0 0.0 -1.0
            Vector L = ray.O - d_position; // L = 0, 0, 200
            double a = ray.D.dot(ray.D);   // 1.0
            double b = 2.0 * ray.D.dot(L); // -400
            double c = L.dot(L) - d_radius * d_radius;

            // light 0.000000 0.000000 200.000000, abc 1.000000 -400.000000 30000.000000

            //if (ray.D.x == 0.0 && ray.D.y == 0)
            //    printf("light %f %f %f, abc %f %f %f", L.x, L.y, L.z, a, b, c);

            double t0;
            double t1;

            bool quadratic_solved = quadratic(a, b, c, t0, t1);
            //if (ray.D.x == 0.0 && ray.D.y == 0)
            //    printf("%f %f", t0, t1);
            if (!quadratic_solved)
            {
                //printf("hi1");
                Hit no_hit{ 0, Vector{} , NULL };
                no_hit.hit = false;
                return no_hit;
                //return Hit::NO_HIT();
            }

            //printf("hi2\n");
            // t0 is closest hit
            if (t0 < 0.0)  // check if it is not behind the camera
            {
                t0 = t1;    // try t1
                if (t0 < 0.0) // both behind the camera
                {
                    //printf("hi3\n");
                    Hit no_hit{ 0, Vector{} , NULL };
                    no_hit.hit = false;
                    return no_hit;
                    //return Hit::NO_HIT();
                }
            }

            // calculate normal
            //printf("hello hit\n");
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


#endif