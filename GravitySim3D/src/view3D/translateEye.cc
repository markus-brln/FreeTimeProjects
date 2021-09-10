#include "view3D.ih"

void View3D::translateEye(double right, double up, double forward)
{
    Vector direction{ right, up, forward };
    rotateVector(direction, d_eyeRotation.x, d_eyeRotation.y, d_eyeRotation.z);

    d_eye += direction;
}
// MB receives the amount of translation in each direction, due to the eye's 
// rotation, this has to be converted into the actual x,y,z translation.
