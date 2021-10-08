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

        
        // --- Constructors ------------------------------------------------------------

        //__host__ __device__ Triple(double X = 0, double Y = 0, double Z = 0);
        //explicit Triple(nlohmann::json const& node);    // json -> Triple

        CUDA_CALLABLE_MEMBER Triple(double X = 0, double Y = 0, double Z = 0)
            :
            x(X),
            y(Y),
            z(Z)
        {}


        // --- Operators ---------------------------------------------------------------

        CUDA_CALLABLE_MEMBER Triple& operator=(Triple const& other)
        {
            x = other.x;
            y = other.y;
            z = other.z;

            return *this;
        }

        CUDA_CALLABLE_MEMBER Triple Triple::operator+(Triple const& t) const
        {
            return Triple(x + t.x, y + t.y, z + t.z);
        }

        CUDA_CALLABLE_MEMBER Triple Triple::operator+(double f) const
        {
            return Triple(x + f, y + f, z + f);
        }

        CUDA_CALLABLE_MEMBER Triple Triple::operator-() const
        {
            return Triple(-x, -y, -z);
        }

        CUDA_CALLABLE_MEMBER Triple Triple::operator-(Triple const& t) const
        {
            return Triple(x - t.x, y - t.y, z - t.z);
        }

        CUDA_CALLABLE_MEMBER Triple Triple::operator-(double f) const
        {
            return Triple(x - f, y - f, z - f);
        }

        CUDA_CALLABLE_MEMBER Triple Triple::operator*(Triple const& t) const
        {
            return Triple(x * t.x, y * t.y, z * t.z);
        }

        CUDA_CALLABLE_MEMBER Triple Triple::operator*(double f) const
        {
            return Triple(x * f, y * f, z * f);
        }

        CUDA_CALLABLE_MEMBER Triple Triple::operator/(double f) const
        {
            double invf = 1.0 / f;
            return Triple(x * invf, y * invf, z * invf);
        }

        //// --- Compound operators ------------------------------------------------------

        CUDA_CALLABLE_MEMBER Triple& Triple::operator+=(Triple const& t)
        {
            x += t.x;
            y += t.y;
            z += t.z;
            return *this;
        }

        CUDA_CALLABLE_MEMBER Triple& Triple::operator+=(double f)
        {
            x += f;
            y += f;
            z += f;
            return *this;
        }

        CUDA_CALLABLE_MEMBER Triple& Triple::operator-=(Triple const& t)
        {
            x -= t.x;
            y -= t.y;
            z -= t.z;
            return *this;
        }

        CUDA_CALLABLE_MEMBER Triple& Triple::operator-=(double f)
        {
            x -= f;
            y -= f;
            z -= f;
            return *this;
        }

        CUDA_CALLABLE_MEMBER Triple& Triple::operator*=(double f)
        {
            x *= f;
            y *= f;
            z *= f;
            return *this;
        }

        CUDA_CALLABLE_MEMBER Triple& Triple::operator/=(double f)
        {
            double invf = 1.0 / f;
            x *= invf;
            y *= invf;
            z *= invf;
            return *this;
        }

        //// --- Vector Operators --------------------------------------------------------

        CUDA_CALLABLE_MEMBER double Triple::dot(Triple const& t) const
        {
            return x * t.x + y * t.y + z * t.z;
        }

        CUDA_CALLABLE_MEMBER Triple Triple::cross(Triple const& t) const
        {
            return Triple(y * t.z - z * t.y,
                z * t.x - x * t.z,
                x * t.y - y * t.x);
        }

        CUDA_CALLABLE_MEMBER double Triple::length() const
        {
            return sqrt(length_2());
        }

        CUDA_CALLABLE_MEMBER double Triple::length_2() const
        {
            return x * x + y * y + z * z;
        }

        CUDA_CALLABLE_MEMBER Triple Triple::normalized() const
        {
            return (*this) / length();
        }

        CUDA_CALLABLE_MEMBER void Triple::normalize()
        {
            double len = length();
            double invlen = 1.0 / len;
            x *= invlen;
            y *= invlen;
            z *= invlen;
        }

        CUDA_CALLABLE_MEMBER Triple reflect(Triple const& normal) const
        {
            Triple temp = *this - 2.0 * normal.dot(*this);

            return  temp * normal;
        }
        // assumes *this is the incident vector!
        // needed to rewrite this one to be a member function, otherwise wouldn't compile,
        // see "Free Operators" below

        // --- Color functions ---------------------------------------------------------

        CUDA_CALLABLE_MEMBER void Triple::set(double f)
        {
            r = f;
            g = f;
            b = f;
        }

        CUDA_CALLABLE_MEMBER void Triple::set(double f, double maxValue)
        {
            set(f / maxValue);
        }
        CUDA_CALLABLE_MEMBER void Triple::set(double red, double green, double blue)
        {
            r = red;
            g = green;
            b = blue;
        }

        CUDA_CALLABLE_MEMBER void Triple::set(double red, double green, double blue, double maxValue)
        {
            set(red / maxValue, green / maxValue, blue / maxValue);
        }

        CUDA_CALLABLE_MEMBER Triple& Triple::clamp(double maxValue = 1)
        {
            r = fmin(r, maxValue);
            g = fmin(g, maxValue);
            b = fmin(b, maxValue);
            return *this;
        }

};

// --- Free Operators ----------------------------------------------------------

//__host__ __device__ Triple operator+(double f, Triple const& t);
//__host__ __device__ Triple operator-(double f, Triple const& t);
//__host__ __device__ Triple operator*(double f, Triple const& t);
//
//// reflect incident in normal
//__host__ __device__ Triple reflect(Triple const& incident, Triple const& normal);
//
//// --- IO Operators ------------------------------------------------------------
//
//__host__ __device__ std::istream& operator>>(std::istream& is, Triple& t);
//__host__ __device__ std::ostream& operator<<(std::ostream& os, Triple const& t);


// --- Free Operators ----------------------------------------------------------
// somehow not working -> "operatorX already defined in [other obj file from source]"
// 
//__host__ __device__ Triple operator+(double f, Triple const& t)
//{
//    return Triple(f + t.x, f + t.y, f + t.z);
//}
//
//__host__ __device__ Triple operator-(double f, Triple const& t)
//{
//    return Triple(f - t.x, f - t.y, f - t.z);
//}
//
//__host__ __device__ Triple operator*(double f, Triple const& t)
//{
//    return Triple(f * t.x, f * t.y, f * t.z);
//}
//
//CUDA_CALLABLE_MEMBER Triple reflect(Triple const& incident, Triple const& normal)
//{
//    return incident - 2.0 * normal.dot(incident) * normal;
//}
//
// 




#endif // !TRIPLE_H