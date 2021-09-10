#include "main.ih"

// define globals
int SIZE = 300;
size_t N_STARS = 80;
double GRAV_CONST = 2;
std::string SCENE = string{};           // a global needs to be defined


int main()
{
    Gravitysim3D gravitysim3D;          // "model" in MVC pattern
    sf::RenderWindow window(            // view paints on the window
        sf::VideoMode(SIZE, SIZE), "Gravity Simulation"
    );    
    window.setFramerateLimit(30);

    View3D view3D{ gravitysim3D };

                                        // controller draws on window, changes model
    Controller controller{ gravitysim3D, view3D, window };

    controller.run();                   // start the game loop

    return 0;
}


// Plan for 3D gravity sim:
/*
- have viewpoint as usual
- determine vertices of a quad (screen) from viewpoint and view vector
- intersect the quad with vector view->Star
- draw on screen (quad)
*/