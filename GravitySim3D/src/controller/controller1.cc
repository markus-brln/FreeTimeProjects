#include "controller.ih"

Controller::Controller(Gravitysim3D &gravitysim3D, View3D &view3D, sf::RenderWindow &window)
:
    d_gravitysim3D(gravitysim3D),
    d_view3D(view3D),
    d_window(window)
{
}

