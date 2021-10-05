#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
#include "../model/model.h"


class Controller
{
    Model &d_model;                     // all data members with d_...
    sf::RenderWindow &d_window;         // sf::Window == view in MVC pattern
    bool d_fullscreen = false;

    public:
        Controller() = delete;
        Controller(Model &model, sf::RenderWindow &window);   // 1.cc

        void run();
        void handleEvent(sf::Event &event);
        void handleKeyPresses();

        //void configureSolarSystem();
        //sf::Text createText();
};



#endif

