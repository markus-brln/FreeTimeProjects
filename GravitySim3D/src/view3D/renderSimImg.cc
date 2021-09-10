#include "view3D.ih"

void View3D::renderSimImg(sf::Image &img)
{
    //int width, height = SIZE;

    Vector down{ 0, -1, 0 };            // vector down from centre of screen
    Vector right{ 1, 0, 0 };            // vector right from centre
    
                                        // no Z-rotation yet
    rotateVector(down, d_eyeRotation.x, d_eyeRotation.y, 0);
    rotateVector(right, d_eyeRotation.x, d_eyeRotation.y, 0);

                                        // camera perpendicular to screen formed
    Vector d_camera = right.cross(down);// by right+down

                                        // *SIZE arbitrary to achieve equilateral 
                                        // pyramid to screen, 60° FOV initially
    Point screenCentre = d_eye + d_camera * SIZE * d_zoom;
    //cout << "eye: " << d_eye << "centre: " << screenCentre << '\n';

    Point upperLeft = screenCentre - (down * SIZE) / 2 - (right * SIZE) / 2;
    Point upperRight = screenCentre - (down * SIZE) / 2 + (right * SIZE) / 2;
    Point lowerRight = screenCentre - (down * SIZE) / 2 + (right * SIZE) / 2;
    Point lowerLeft = screenCentre + (down * SIZE) / 2 - (right * SIZE) / 2;
    

    Quad screen{ upperLeft, upperRight, lowerRight, lowerLeft };

    //int num = 0;
    for (Star &star : d_gravitysim3D.stars())
    {
        Ray ray{ d_eye, star.d_pos - d_eye };

        Hit hit = screen.intersect(ray);

        //if (hit.t != std::numeric_limits<double>::quiet_NaN())
        if (hit.t > 0)                      // not NaN
        {
            //num += 1;
            //cout << hit.t << '\n';

            Point intersection = ray.O + ray.D * hit.t;
            Vector screenCoords = screen.toUV(intersection);
            //cout << " " << distance3D(intersection, ray.O);
            sf::Uint8 brightness = 255;//1 / distance3D(intersection, ray.O) * 255;
            
            sf::Color col;
            if (star.d_mass > 100)
                col = sf::Color{ brightness, 0, 0 };
            else
                col = sf::Color{ brightness, brightness, brightness };

            img.setPixel(screenCoords.x * SIZE, screenCoords.y * SIZE, col);
        }


    }
    //cout << num;
    //exit(0);
}
// This function constructs an imaginary screen some distance away from the viewer's
// eye. It tries to intercept rays from the view to the stars on the screen, if this
// is successful the star is drawn.
// 