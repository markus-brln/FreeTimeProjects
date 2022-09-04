#ifndef UTILS_H
#define UTILS_H

#include "../json/json.h"
#include <SFML/Graphics.hpp>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using json = nlohmann::json;


extern bool FULL_SCREEN;
extern bool SHOW_FPS;
extern size_t SIZE_X;
extern size_t SIZE_Y;
extern string FONT_PATH;
extern size_t FONT_SIZE;
extern sf::Color FONT_COLOR;
extern size_t MAX_ITER;



void parseConfig(const string &filename = "config.json");

#endif

