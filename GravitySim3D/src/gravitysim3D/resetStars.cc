#include "gravitysim3D.ih"

void Gravitysim3D::resetStars()
{
    d_stars.clear();

    d_stars.push_back(Star{Point{0, 0, 0}, Vector{0, 0, 0}, 10000});
    
    for (size_t idx = 0; idx < N_STARS; ++idx)
    {
        double x = randDouble(-SIZE, SIZE);
        double y = randDouble(-SIZE, SIZE);
        double z = 0;//randDouble(0, SIZE);
        double mass = randDouble(1, 5);
        double motion_x = -y / 300 + randDouble(-0.2, 0.2);
        double motion_y = x / 300 + randDouble(-0.2, 0.2);
        double motion_z = randDouble(-0.2, 0.2);
        
        d_stars.push_back(Star{Point{x, y, z}, Vector{motion_x, motion_y, motion_z}, mass});
    }
}

