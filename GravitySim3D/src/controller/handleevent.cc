#include "controller.ih"


void Controller::handleEvent(Event &event)
{
    if (event.type == sf::Event::Closed)
        d_window.close();

    if (event.type == sf::Event::EventType::KeyPressed)
    {
        switch (event.key.code)
        {
        // Reset
        case (sf::Keyboard::Backspace):
            d_gravitysim3D.resetStars();
            break;
        
        case (sf::Keyboard::Space):      
            if (d_stopSim == true)
                d_stopSim = false;       
            else
                d_stopSim = true;    
            //SolarSystemSimOn = !SolarSystemSimOn;   // switch bool
            break;

        default:
            break;
        }
    }
}
// for closing and reset, events that should just happen once -> not live input

