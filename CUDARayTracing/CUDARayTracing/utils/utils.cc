#include "utils.h"

string current_path_string_windows() 
{
	char buff[MAX_PATH];
	GetModuleFileName(NULL, buff, MAX_PATH);
	string::size_type position = string(buff).find_last_of("\\/");
	cout << "current working directory: " << string(buff).substr(0, position) << '\n';
	return string(buff).substr(0, position);
}

double distance2D(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
// distance between 2 2D points

double distance3D(Triple t1, Triple t2)
{
    return sqrt(pow(t1.x - t2.x, 2) + pow(t1.y - t2.y, 2) + pow(t1.z - t2.z, 2));
}
// distance between 2 3D points

double angle(Triple a, Triple b)
{
    return std::acos(a.dot(b) / (a.length() * b.length()));
}
// angle between 2 3D vectors


void rotateVector(Vector& vec, double x_rot, double y_rot, double z_rot)
{
    // ASCII way of writing the matrices & vectors down taken from:
    // https://stackoverflow.com/questions/14607640/rotating-a-vector-in-3d-space

    // rotation around x
    //|1     0           0| |x|   |        x        |   |x'|
    //|0   cos θ    −sin θ| |y| = |y cos θ − z sin θ| = |y'|
    //|0   sin θ     cos θ| |z|   |y sin θ + z cos θ|   |z'|
    Vector vecCopy{ vec };
    // vec.x = same
    vec.y = vecCopy.y * cos(x_rot) - vecCopy.z * sin(x_rot);
    vec.z = vecCopy.y * sin(x_rot) + vecCopy.z * cos(x_rot);

    // roation around y
    //| cos θ    0   sin θ| |x|   | x cos θ + z sin θ|   |x'|
    //|   0      1       0| |y| = |         y        | = |y'|
    //|−sin θ    0   cos θ| |z|   |−x sin θ + z cos θ|   |z'|
    vecCopy = vec;
    vec.x = vecCopy.x * cos(y_rot) + vecCopy.z * sin(y_rot);
    // vec.y = same
    vec.z = -vecCopy.x * sin(y_rot) + vecCopy.z * cos(y_rot);

    // rotation around z
    // |cos θ   −sin θ   0| |x|   |x cos θ − y sin θ|   |x'|
    // |sin θ    cos θ   0| |y| = |x sin θ + y cos θ| = |y'|
    // |  0       0      1| |z|   |        z        |   |z'|
    vecCopy = vec;
    vec.x = vecCopy.x * cos(z_rot) - vecCopy.y * sin(z_rot);
    vec.y = vecCopy.x * sin(z_rot) + vecCopy.y * cos(z_rot);
    // vec.z = same
}
// operates on ref of Vector obj


void rotateVectorAroundVector(Vector& vec, Vector const& axis, double angle)
{
    Vector kUnit = axis.normalized();   // axis needs to be unit vector

    vec = vec * cos(angle) + kUnit.cross(vec) * sin(angle) + kUnit * kUnit.dot(vec) * (1 - cos(angle));
}
// probably useful for rotation around camera vector (initially z-axis)
// using the Rodrigues' rotation formula:
// https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula

__device__ bool quadratic_host(double a, double b, double c,
    double& x0, double& x1)
{
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
        std::swap(x0, x1);

    return true;
}


//--- IO Operators ------------------------------------------------------------
// only for __host__, moved from raytracing/triple.h
istream& operator>>(istream& is, Triple& t)
{
    double x, y, z;
    //  is >> x >> y >> z;      // is not guaranteed to work pre C++17
    is >> x;
    is >> y;
    is >> z;
    t.set(x, y, z);             // only assign if everything is extracted
    return is;
}

ostream& operator<<(ostream& os, Triple const& t)
{
    // format: [x, y, z] (no newline)
    os << '[' << t.x << ", " << t.y << ", " << t.z << ']';
    return os;
}

