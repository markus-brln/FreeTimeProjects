#include "controller.ih"


void Controller::handleKeyPresses()
{
    // double movement = MOVEMENT_BASE * MOVEMENT_MUL;
    // // Translation
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        d_model.translate(0.0, -0.1 / d_model.zoom());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        d_model.translate(0.0, 0.1 / d_model.zoom());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        d_model.translate(-0.1 / d_model.zoom(), 0.0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        d_model.translate(0.1 / d_model.zoom(), 0.0);

    // Rotation (taking zoom into account)
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    //     d_raytracer.scene.getEyeRotation().x += 0.05 / d_raytracer.scene.getZoom();
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    //     d_raytracer.scene.getEyeRotation().x -= 0.05 / d_raytracer.scene.getZoom();
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    //     d_raytracer.scene.getEyeRotation().y += 0.05 / d_raytracer.scene.getZoom();
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    //     d_raytracer.scene.getEyeRotation().y -= 0.05 / d_raytracer.scene.getZoom();
    // for now not active, would require even more rotation I think
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
    //    d_raytracer.scene.getEyeRotation().z -= 0.05;
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
    //    d_raytracer.scene.getEyeRotation().z += 0.05;

    // Zoom
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
        d_model.multZoom(1.05);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
        d_model.multZoom(1.0 / 1.05);
    
}
// this is for live input (allowing for multiple input actions at the same time),
// nice tutorial about it: https://www.youtube.com/watch?v=hZ2WogmdLPo&t=76s

