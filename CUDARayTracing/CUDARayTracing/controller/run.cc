#include "controller.ih"
#include "../utils/utils.h"

void Controller::run()
{
    sf::Clock clock;                    // for frame rate
    sf::Event event;
    sf::Image img;                      // image of which the pixels are set 
                                        // through raytracing


    double fpsAvrg = 0;                 // update FPS average after each frame
    double frameNr = 1;

    sf::Texture texture;                // Texture made from Image
    sf::Sprite sprite;                  // Sprite whose Texture is set

    sf::Text text;                      // for displaying fps
    sf::Font font;

    font.loadFromFile(current_path_string_windows() + "\\fonts\\jackInputMonospace.TTF");
    text.setFont(font);
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::White);


    while (d_window.isOpen())
    {
        while (d_window.pollEvent(event))
            handleEvent(event);         // closing, reset, toggle fullscreen
        handleKeyPresses();             // live input


        unsigned char *pixelData = d_model.renderImage();    // heavy work

        img.create(SIZE_X, SIZE_Y, pixelData);
        texture.loadFromImage(img);     //Load Texture from image
        sprite.setTexture(texture);
        
        // FPS display & documentation
        text.setString("fps: " + to_string(1000000 / clock.getElapsedTime().asMicroseconds()));
        fpsAvrg += (1000000 / clock.getElapsedTime().asMicroseconds() - fpsAvrg) / frameNr;
        frameNr++;

        clock.restart();
        d_window.clear();             // not sure whether this is needed, probably not
                                        // since whole screen is refreshed
        d_window.draw(sprite);
        d_window.draw(text);
        d_window.display();        

        //return;
    }

    cout << "fpsAvrg: " << fpsAvrg;
}


