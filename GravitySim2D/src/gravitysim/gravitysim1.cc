#include "gravitysim.ih"

Gravitysim::Gravitysim()
{
    d_stars.push_back(Star{400, 400, 1000, vector<double>{0, 0}});
    
    for (size_t idx = 0; idx < N_STARS; ++idx)
    {
        double x = randDouble(0, SIZE);
        double y = randDouble(0, SIZE);
        double mass = 5;//randDouble(1, 5);
        double motion_x = randDouble(-0.2, 0.2);
        double motion_y = randDouble(-0.2, 0.2);
        
        d_stars.push_back(Star{x, y, mass, vector<double>{motion_x, motion_y}});
    }
}

