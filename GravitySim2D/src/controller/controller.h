#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
//#include "../raytracerandfriends/raytracer.h"
//#include "../raytracerandfriends/shapes/sphere.h"
#include "../gravitysim/gravitysim.h"


class Controller
{
    Gravitysim &d_gravitysim;
    sf::RenderWindow &d_window;         // sf::Window == view in MVC pattern
    

    public:
        Controller() = delete;
        Controller(Gravitysim &gravitysim, sf::RenderWindow &window);   // 1.cc

        void run();
        void handleEvent(sf::Event &event);
        void handleKeyPresses();

        //void configureSolarSystem();
        sf::Text createText();
};



#endif

