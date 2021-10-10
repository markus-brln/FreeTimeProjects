#include "controller.ih"

 
void Controller::handleKeyPresses()
{
    // Translation
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        d_model.translateEye(0, 0, -30);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        d_model.translateEye(0, 0, 30);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        d_model.translateEye(-30, 0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        d_model.translateEye(30, 0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        d_model.translateEye(0, 30, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        d_model.translateEye(0, -30, 0);

    // Rotation (taking zoom into account)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        d_model.rotateEye(0.05 / d_model.getZoom(), 0.0, 0.0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        d_model.rotateEye(-0.05 / d_model.getZoom(), 0.0, 0.0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        d_model.rotateEye(0.0, 0.05 / d_model.getZoom(), 0.0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        d_model.rotateEye(0.0, -0.05 / d_model.getZoom(), 0.0);
    // for now not active, would require even more rotation I think
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
    //    d_raytracer.scene.getEyeRotation().z -= 0.05;
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
    //    d_raytracer.scene.getEyeRotation().z += 0.05;

    // Zoom
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
        d_model.zoomIn(1.05);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
        d_model.zoomIn(0.95);
}
// this is for live input (allowing for multiple input actions at the same time),
// nice tutorial about it: https://www.youtube.com/watch?v=hZ2WogmdLPo&t=76s

