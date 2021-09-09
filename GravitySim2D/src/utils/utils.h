#ifndef UTILS_H
#define UTILS_H

#include "../raytracerandfriends/triple.h"      // not really needed, stayed here because of laziness
#include <cmath>
#include <string>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

using namespace std;

// my setup for random numbers, see randDouble() in utils.cc
static random_device rand_dev;
static mt19937 generator(rand_dev());
static uniform_real_distribution<double>  uniformDist(0, 1);


// GLOBALS
extern int SIZE;
extern size_t N_STARS;
extern double GRAV_CONST;
//extern int UPSCALED;
extern string SCENE;
extern bool SolarSystemSimOn;


// USEFUL FUNCTIONS
double randDouble(double min, double max);
double distance2D(double x1, double y1, double x2, double y2);
double distance3D(Triple t1, Triple t2);
double angle(Triple a, Triple b);
void rotateVector(Vector &vec, double x_rot, double y_rot, double z_rot);
void rotateVectorAroundVector(Vector &vec, Vector const &axis, double angle);
void chooseScene();
void upscaleSFImage(sf::Image &image);      // failed attempt

#endif

