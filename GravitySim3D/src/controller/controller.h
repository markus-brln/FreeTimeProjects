#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <SFML/Graphics.hpp>
#include "../gravitysim3D/gravitysim3D.h"
#include "../view3D/view3D.h"


class Controller
{
    Gravitysim3D &d_gravitysim3D;
    View3D &d_view3D;
    sf::RenderWindow &d_window;

    bool d_stopSim = false;

    public:
        Controller() = delete;
        Controller(Gravitysim3D &gravitysim3D, View3D &view3D, 
                   sf::RenderWindow &window);                   // 1.cc

        void run();
        void handleEvent(sf::Event &event);
        void handleKeyPresses();

        sf::Text createText();
};



#endif

