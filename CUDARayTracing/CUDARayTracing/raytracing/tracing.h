#include "../utils/utils.h"
#include "triple.h"
#include "hit.h"
#include "ray.h"
#include "light.h"
#include "objects/obj.h"
#include "cuda_runtime.h"

//__device__ double sqrt(double num)
//{
//    double sqrt = num / 2;
//    double temp = 0.00001;
//
//    // Iterate until sqrt is different of temp, that is updated on the loop
//    while (sqrt > temp) 
//    {
//        // initially 0, is updated with the initial value of 128
//        // (on second iteration = 65)
//        // and so on
//        temp = sqrt;
//
//        // Then, replace values (256 / 128 + 128 ) / 2 = 65
//        // (on second iteration 34.46923076923077)
//        // and so on
//        sqrt = (num / temp + temp) / 2;
//    }
//
//    return sqrt;
//}

__device__ double distance3D_device(Triple t1, Triple t2)
{
    return sqrt(
        (t1.x - t2.x) * (t1.x - t2.x) + 
        (t1.y - t2.y) * (t1.y - t2.y) +
        (t1.z - t2.z) * (t1.z - t2.z));
}

__device__ double angle_device(Triple const &a, Triple const &b)
{
    return std::acos(a.dot(b) / (a.length() * b.length()));
}
// angle between 2 3D vectors

__device__ double pow_device(double num, size_t power)
{
    while (power-- != 0)
        num *= num;

    return num;
}

__device__ Hit castRay(Ray const& ray, Obj** objects, size_t n_objects)
{
    // Find hit object and distance
    Hit min_hit = Hit::NO_HIT();
    Obj* obj = nullptr;
    for (unsigned idx = 0; idx != n_objects; ++idx)
    {
        Hit hit(objects[idx]->intersect(ray));
        if (hit.hit && hit.t < min_hit.t)
        {
            min_hit = hit;
            min_hit.hitObj = objects[idx];
            //printf("new obj found\n");
        }
    }

    return min_hit;
}
// provided in CG course, find hit with object, if any


__device__ bool lightObstructed(Light *light, Point const& hit, Vector const& normalFromObj, Obj **objects, int n_objects)
{
    // Offset multiplier. Before casting a new ray from a hit point,
    // move the hit point in the direction of the normal with this offset
    // to prevent finding an intersection with the same object due to
    // floating point inaccuracies. This prevents shadow acne, among other problems.
    double const epsilon = 1E-3;

    // from the hitpoint + some N dir to view
    Point hoveringHit = hit + normalFromObj * epsilon;
    Ray shadowRay = Ray{ hoveringHit, light->position - hoveringHit };
    Hit mainhit = castRay(shadowRay, objects, n_objects);


    if (!mainhit.hitObj)                 // first == object pointer, nullptr if no hit
        return false;                   // No hit? No obstruction.

    //if (mainhit.first->objComment == "Sun") // light not obstructed by Sun's sphere!
    //    return false;

    Point objHitPoint = shadowRay.O + shadowRay.D * mainhit.t;
    if (distance3D_device(light->position, hoveringHit) < distance3D_device(objHitPoint, hoveringHit))
        return false;

    return true;
}
// look whether the light source is obstructed from its origin to the point
// where it would hit the object

 
__device__ Color trace(Ray const& ray, unsigned recursionDepth, Obj** objects, int n_objects, Light **lights, int n_lights)
{
    //printf("n_objects %d, object1radius: %f, posz %f\n", n_objects, objects[0]->d_radius, objects[0]->d_position.z);
    Hit min_hit = castRay(ray, objects, n_objects);
    Obj* obj = static_cast<Obj*>(min_hit.hitObj);

    //printf("object1radius: %f, posz %d\n", objects[0]->d_radius,
    //	objects[0]->d_position.z);

    // No hit? Return background color.
    if (!min_hit.hit)
        return Color{ 0.0, 0.0, 0.0 };
    //else
    //{
    //    //printf("HIT\n");
    //    return Color{ 1.0, 1.0, 1.0 };
    //}

    //Material const &material = obj->material;
    Point hit = ray.at(min_hit.t);
    Vector V = -ray.D;

    // Pre-condition: For closed objects, N points outwards.
    Vector N = min_hit.N;

    // The shading normal always points in the direction of the view,
    // as required by the Phong illumination model.
    Vector shadingN;
    if (N.dot(V) >= 0.0)
        shadingN = N;
    else
        shadingN = -N;

    // -------- Texture mapping code
    Color matColor;
    if (obj->hasTexture) {
        //Vector uvVector = obj->toUV(hit);
        //matColor = material.texture.colorAt(uvVector.x, 1.0 - uvVector.y);
        //if (obj->isSkybox)                  // MB stop reflection etc if the 
        //    return matColor;                // object is part of the skybox 
        //                                    // as determined in json under "comment": "Skybox..."
        matColor = obj->d_color;
    }
    else 
    {
        matColor = obj->d_color;
    }
    //-----------

    //// Add ambient once, regardless of the number of lights.
    Color color = matColor * obj->ka;

    //// Add diffuse and specular components.
    //for (auto const& light : lights)
    for (size_t idx = 0; idx < n_lights; ++idx)
    {
        // OUR CODE BEGIN
        if (lightObstructed(lights[idx], hit, shadingN, objects, n_objects)) // && renderShadows
            continue;
        // OUR CODE END

        Vector L = (lights[idx]->position - hit).normalized();

        // Add diffuse.
        double dotNormal = shadingN.dot(L);
        double diffuse = dotNormal > 0.0 ? dotNormal : 0.0; //std::max(dotNormal, 0.0);
        color += lights[idx]->color * matColor * diffuse * obj->kd;

        // Add specular.
        if (dotNormal > 0)
        {
            Vector reflectDir = Vector{ -L }.reflect(shadingN);  // reflect(-L, shadingN); // Note: reflect(..) is not given in the framework.
            double dot1 = reflectDir.dot(V);
            double specAngle = dot1 > 0.0 ? dot1 : 0.0; //std::max(reflectDir.dot(V), 0.0);

            double specular = 1;
            if (obj->n > 0 && obj->n == int(obj->n))
            {
                for (int power = 0; power < obj->n; ++power)
                    specular *= specAngle;
            }
            //double specular = pow(specAngle, obj->n);// std::pow(specAngle, obj->n);

            color +=  lights[idx]->color * specular * obj->ks;
        }
    }

    double const epsilon = 1E-3;

    if (recursionDepth > 0 && obj->isTransparent)
    {
        //printf("hellooo");
        // our code begin

        // the object is transparent, and thus refracts and reflects light.
        // use schlick's approximation to determine the ratio between the two.
        double n_i = 1.0;           // refractive idx outside obj (like air)
        double n_t = obj->nt;   // refractive index of obj

        if (N.dot(V) < 0.0)         // light ray is exiting the obj
        {
            double swapnum = n_i;   // from obj -> air!
            n_i = n_t;
            n_t = swapnum;
        }
            


        // reflection
                                    // normal procedure like for opaque obj
        Vector refldir = ray.D.reflect(shadingN); //reflect(ray.d, shadingn);
        Ray reflectray{ hit + shadingN * epsilon, refldir };


        // refraction
        // see slide 71
        Vector part1 = ((ray.D - shadingN * ray.D.dot(shadingN)) * n_i / n_t);
        double undersqrt = 1 - (
            pow_device(n_i, 2) * (
                1 - pow_device(ray.D.dot(shadingN), 2)
                ) / pow_device(n_t, 2)
            );

        Vector part2 = shadingN * sqrt(undersqrt);
        Vector refrdir = part1 - part2;     // vector t on slide 71

                            // "-" other dir because to the inside!!
        Ray refractray{ hit - shadingN * epsilon, refrdir };


        // ratio reflected/refracted

        double k_r;                     // intensity multiplier of reflected ray
        double k_t;                     // ~ of transmitted (refracted) ray          

        if (undersqrt < 0 && N.dot(V) < 0.0)// total *internal* reflection, slide 71
        {
            k_r = 1;                        // slide  76
            k_t = 0;
        }
        else
        {
            double k_r0 = (n_i - n_t) / (n_i + n_t) * (n_i - n_t) / (n_i + n_t);  // slide 76
            double phi = angle_device(-ray.D, shadingN);   // between light and normal on obj


            k_r = k_r0 + (1 - k_r0) * pow_device((1 - cos(phi)), 5);
            k_t = 1 - k_r;
        }

        // give color slide 75
        recursionDepth--;
        color = color + trace(reflectray, recursionDepth, objects, n_objects, lights, n_lights) * k_r; // i = kr * i(p,r)
        color = color + trace(refractray, recursionDepth, objects, n_objects, lights, n_lights) * k_t;

    }
    else if (recursionDepth > 0 && obj->ks > 0.0)
    {
        //printf("hellooo1");
        // the object is not transparent, but opaque.
        Vector reflectdirection = ray.D.reflect(shadingN); //reflect(ray.d, shadingN);

        Point hoveringhit = hit + shadingN * epsilon;

        Ray reflectray{ hoveringhit, reflectdirection };

        // 2.2.4 don't forget to reduce depth
        recursionDepth--;
        color = color + trace(reflectray, recursionDepth, objects, n_objects, lights, n_lights) * obj->ks;

        // our code end
    }

    //printf("hellooo2");

    return color;
}