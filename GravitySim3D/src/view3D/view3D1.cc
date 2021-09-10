#include "view3D.ih"


View3D::View3D(Gravitysim3D &gravitysim3D)
:
    d_gravitysim3D(gravitysim3D)
{
    sf::RenderWindow window(            // view paints on the window
        sf::VideoMode(SIZE, SIZE), "Gravity Simulation"
    );
    window.setFramerateLimit(30);
}