#include "../utils/utils.h"
#include "../raytracing/triple.h"
#include "../raytracing/hit.h"
#include "../raytracing/light.h"
#include "../raytracing/objects/object.h"


__device__ Hit castRay(Ray const& ray, Object **objects, size_t n_objects)
{
    // Find hit object and distance
    Hit min_hit = Hit::NO_HIT();
    Object *obj = nullptr;
    for (unsigned idx = 0; idx != n_objects; ++idx)
    {
        Hit hit(objects[idx]->intersect(ray));
        if (hit.t < min_hit.t)
        {
            min_hit = hit;
            min_hit.hitObj = objects[idx];
        }
    }

    return min_hit;
}
// provided in CG course, find hit with object, if any


//bool lightObstructed(Light *light, Point const& hit, Vector const& normalFromObj)
//{
//    // Offset multiplier. Before casting a new ray from a hit point,
//    // move the hit point in the direction of the normal with this offset
//    // to prevent finding an intersection with the same object due to
//    // floating point inaccuracies. This prevents shadow acne, among other problems.
//    double const epsilon = 1E-3;
//
//    // from the hitpoint + some N dir to view
//    Point hoveringHit = hit + normalFromObj * epsilon;
//    Ray shadowRay = Ray{ hoveringHit, light->position - hoveringHit };
//    pair<Object*, Hit> mainhit = castRay(shadowRay);
//
//
//    if (!mainhit.first)                 // first == object pointer, nullptr if no hit
//        return false;                   // No hit? No obstruction.
//
//    //if (mainhit.first->objComment == "Sun") // light not obstructed by Sun's sphere!
//    //    return false;
//
//    Point objHitPoint = shadowRay.O + mainhit.second.t * shadowRay.D;
//    if (distance3D(light->position, hoveringHit) < distance3D(objHitPoint, hoveringHit))
//        return false;
//
//    return true;
//}
//// look whether the light source is obstructed from its origin to the point
//// where it would hit the object
//

__device__ Color trace(Ray const& ray, unsigned depth, Object **objects, size_t n_objects)
{
    Hit min_hit = castRay(ray, objects, n_objects);
    Object *obj = static_cast<Object*>(min_hit.hitObj);


    // No hit? Return background color.
    if (!obj)
    {
        return Color(0.0, 0.0, 0.0);
    }
    else
    {
        return Color{ 1, 1, 1 };
    }

    //Material const& material = obj->material;
    //Point hit = ray.at(min_hit.t);
    //Vector V = -ray.D;

    //// Pre-condition: For closed objects, N points outwards.
    //Vector N = min_hit.N;

    //// The shading normal always points in the direction of the view,
    //// as required by the Phong illumination model.
    //Vector shadingN;
    //if (N.dot(V) >= 0.0)
    //    shadingN = N;
    //else
    //    shadingN = -N;

    //// -------- Texture mapping code
    //Color matColor;
    //if (material.hasTexture) {
    //    Vector uvVector = obj->toUV(hit);
    //    matColor = material.texture.colorAt(uvVector.x, 1.0 - uvVector.y);
    //    if (obj->isSkybox)                  // MB stop reflection etc if the 
    //        return matColor;                // object is part of the skybox 
    //                                        // as determined in json under "comment": "Skybox..."
    //}
    //else {
    //    matColor = material.color;
    //}
    ////-----------

    //// Add ambient once, regardless of the number of lights.
    //Color color = material.ka * matColor;

    //// Add diffuse and specular components.
    //for (auto const& light : lights)
    //{
    //    // OUR CODE BEGIN
    //    if (renderShadows && lightObstructed(light, hit, shadingN))
    //        continue;
    //    // OUR CODE END

    //    Vector L = (light->position - hit).normalized();

    //    // Add diffuse.
    //    double dotNormal = shadingN.dot(L);
    //    double diffuse = std::max(dotNormal, 0.0);
    //    color += diffuse * material.kd * light->color * matColor;

    //    // Add specular.
    //    if (dotNormal > 0)
    //    {
    //        Vector reflectDir = reflect(-L, shadingN); // Note: reflect(..) is not given in the framework.
    //        double specAngle = std::max(reflectDir.dot(V), 0.0);
    //        double specular = std::pow(specAngle, material.n);

    //        color += specular * material.ks * light->color;
    //    }
    //}

    //if (depth > 0 and material.isTransparent)
    //{
    //    // OUR CODE BEGIN

    //    // The object is transparent, and thus refracts and reflects light.
    //    // Use Schlick's approximation to determine the ratio between the two.
    //    double n_i = 1.0;           // refractive idx outside obj (like air)
    //    double n_t = material.nt;   // refractive index of obj

    //    if (N.dot(V) < 0.0)         // light ray is exiting the obj
    //        swap(n_i, n_t);         // from obj -> air!


    //    // REFLECTION
    //                                // normal procedure like for opaque obj
    //    Vector reflDir = reflect(ray.D, shadingN);
    //    Ray reflectRay{ hit + epsilon * shadingN, reflDir };


    //    // REFRACTION
    //    // see slide 71
    //    Vector part1 = (n_i * (ray.D - ray.D.dot(shadingN) * shadingN) / n_t);
    //    double underSqrt = 1 - (
    //        pow(n_i, 2) * (
    //            1 - pow(ray.D.dot(shadingN), 2)
    //            ) / pow(n_t, 2)
    //        );

    //    Vector part2 = shadingN * sqrt(underSqrt);
    //    Vector refrDir = part1 - part2;     // vector T on slide 71

    //                        // "-" other dir because to the inside!!
    //    Ray refractRay{ hit - epsilon * shadingN, refrDir };


    //    // RATIO REFLECTED/REFRACTED

    //    double k_r;                     // intensity multiplier of reflected ray
    //    double k_t;                     // ~ of transmitted (refracted) ray          

    //    if (underSqrt < 0 && N.dot(V) < 0.0)// total *internal* reflection, slide 71
    //    {
    //        k_r = 1;                        // slide  76
    //        k_t = 0;
    //    }
    //    else
    //    {
    //        double k_r0 = pow((n_i - n_t) / (n_i + n_t), 2);  // slide 76
    //        double phi = angle(-ray.D, shadingN);   // between light and normal on obj


    //        k_r = k_r0 + (1 - k_r0) * pow((1 - cos(phi)), 5);
    //        k_t = 1 - k_r;
    //    }

    //    // GIVE COLOR slide 75
    //    depth--;
    //    color = color + k_r * trace(reflectRay, depth); // I = kr * I(P,R)
    //    color = color + k_t * trace(refractRay, depth);

    //}
    //else if (depth > 0 and material.ks > 0.0)
    //{
    //    // The object is not transparent, but opaque.
    //    Vector reflectDirection = reflect(ray.D, shadingN);

    //    Point hoveringHit = hit + 0.001 * shadingN;

    //    Ray reflectRay{ hoveringHit, reflectDirection };

    //    // 2.2.4 don't forget to reduce depth
    //    color = color + obj->material.ks * trace(reflectRay, depth--);

    //    // OUR CODE END
    //}

    //return color;
}