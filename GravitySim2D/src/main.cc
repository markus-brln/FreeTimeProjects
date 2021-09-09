#include "main.ih"

// define globals
int SIZE = 800;
size_t N_STARS = 1000;
double GRAV_CONST = 0.05;
std::string SCENE = string{};           // a global needs to be defined


int main()
{
    //chooseScene();                      // utils.cc

    //Raytracer raytracer;                
    Gravitysim gravitysim;              // "model" in MVC pattern
    sf::RenderWindow window(            // sf::Window is view 
        sf::VideoMode(SIZE, SIZE), "Gravity Simulation"
    );    
    window.setFramerateLimit(30);

                                        // controller draws on window, changes model
    Controller controller{ gravitysim, window };

    controller.run();                   // start the game loop

    return 0;
}
