#include "gravitysim3D.ih"


void Gravitysim3D::timestep()
{
    vector<Star> movedStars = d_stars;

    # pragma omp parallel for
    for (size_t idx1 = 0; idx1 < d_stars.size(); ++idx1)
    {
        for (size_t idx2 = 0; idx2 < d_stars.size(); ++idx2)
        {
            if (idx1 == idx2)               // do not calculate for the planet itself
                continue;
            
            Vector delta_pos = d_stars[idx2].d_pos - d_stars[idx1].d_pos;
            double radius = distance3D(d_stars[idx2].d_pos, d_stars[idx1].d_pos);

            movedStars[idx1].d_motion += GRAV_CONST * delta_pos / (d_stars[idx1].d_mass * (radius * radius));


            /*double radius = distance2D(d_stars[idx1].d_x, d_stars[idx1].d_y, d_stars[idx2].d_x, d_stars[idx2].d_y);
            double delta_x = d_stars[idx2].d_x - d_stars[idx1].d_x;
            double delta_y = d_stars[idx2].d_y - d_stars[idx1].d_y;

                                            // loosely following the formula for gravitational force
            movedStars[idx1].d_motion[0] += GRAV_CONST * delta_x * d_stars[idx2].d_mass / (d_stars[idx1].d_mass * (radius * radius));
            movedStars[idx1].d_motion[1] += GRAV_CONST * delta_y * d_stars[idx2].d_mass / (d_stars[idx1].d_mass * (radius * radius));*/
        }
        movedStars[idx1].d_pos += movedStars[idx1].d_motion;

        //movedStars[idx1].d_x += movedStars[idx1].d_motion[0];
        //movedStars[idx1].d_y += movedStars[idx1].d_motion[1];
    }

    d_stars = movedStars;
    
}