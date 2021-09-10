#ifndef VIEW3D_H
#define VIEW3D_H

#include "../gravitysim3D/gravitysim3D.h"

class View3D
{
    Gravitysim3D &d_gravitysim3D;           // reference to "model" to display
    
    Point d_eye{0, 0, 2000};                // position of the viewer
    Vector d_eyeRotation;                   // deviation from looking along Z-axis
    Vector d_camera;                        // direction of the view based on rotation
    double d_zoom = 1.0;                    // determines how far away the
                                            // imaginary screen -> changes 
                                            // angle of field of view

    public:
        View3D() = delete;
        View3D(Gravitysim3D &gravitysim3D);

        void renderSimImg(sf::Image &img);

                                            // x, y, z but rotated!
        void translateEye(double right, double up, double forward);
        void setEye(Triple const &position) { d_eye = position; }
        void setEyeRotation(Triple const &rotation) { d_eyeRotation = rotation; }

        Triple &getEye() { return d_eye; }
        Triple &getEyeRotation() { return d_eyeRotation; }
        // MB returning references to the eye position&rotation
        // such that the controller can change them

        void zoom(double value) { d_zoom *= value; }
        // exponential change in zoom value -> steady zoom for eye
        double getZoom() { return d_zoom; }
};


#endif