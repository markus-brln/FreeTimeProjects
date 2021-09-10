#include "gravitysim3D.ih"



/*
sf::Vector2u size = img.getSize();
int w = size.x;
int h = size.y;                     // could be replaced by SIZE


Vector down{ 0, -1, 0 };            // vector down from centre of screen
Vector right{ 1, 0, 0 };            // vector right from centre

                                    // no Z-rotation yet
rotateVector(down, eyeRotation.x, eyeRotation.y, 0);
rotateVector(right, eyeRotation.x, eyeRotation.y, 0);

                                    // camera perpendicular to screen formed
Vector d_camera = right.cross(down);// by right+down


Point screenCentre = eye + d_camera * SIZE * d_zoom;


//#pragma acc kernels loop          // experiment with OpenACC
# pragma omp parallel for
for (int y = 0; y < h; ++y)
{
    for (int x = 0; x < w; ++x)
    {
        // go from top left to bottom right, using the 3 rotated vectors
        Point pixel = screenCentre + (x - SIZE/2) * right + (y - SIZE/2) * down;

        Ray ray(eye, (pixel - eye).normalized());   // shoot ray through pixel

*/