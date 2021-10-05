#include "controller.ih"
#include <string>

void Controller::handleEvent(Event &event)
{
    if (event.type == sf::Event::Closed)
        d_window.close();

    if (event.type == sf::Event::EventType::KeyPressed)
    {
        switch (event.key.code)
        { 
        case (sf::Keyboard::F):
            if (d_fullscreen)
            {
                d_window.create(sf::VideoMode::getFullscreenModes()[0], "Raytracing");
            }
            else
                d_window.create(sf::VideoMode(SIZE_X, SIZE_Y), "Raytracing");
            d_fullscreen = !d_fullscreen;
            // Reset
        //case (sf::Keyboard::Backspace):
        //    d_raytracer.scene.getEye() = Vector{ 0, 0, 2000 };
        //    d_raytracer.scene.getEyeRotation() = Vector{ 0, 0, 0 };
        //    break;
        default:
            break;
        }
    }
}
// for closing and reset, events that should just happen once -> not live input

