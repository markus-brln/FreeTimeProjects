#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include "../utils/utils.h"


class Model
{
    sf::Vector2f d_pos{ 0.0, 0.0 };
    double d_zoom = 1.0;

    public:
        void multZoom(double factor);
        void translate(double x, double y);
        sf::Vector2f pos();
        double zoom();
        void render(sf::Image &img);
        void setPos(const sf::Vector2f &pos);
        void setZoom(double zoom);
};

inline void Model::multZoom(double factor)
{
    d_zoom *= factor;
}

inline void Model::translate(double x, double y)
{
    d_pos.x += x;
    d_pos.y += y;
}

inline sf::Vector2f Model::pos()
{
    return d_pos;
}

inline double Model::zoom()
{
    return d_zoom;
}

inline void Model::setPos(const sf::Vector2f &pos)
{
    d_pos = pos;
}

inline void Model::setZoom(double zoom)
{
    d_zoom = zoom;
}

#endif

