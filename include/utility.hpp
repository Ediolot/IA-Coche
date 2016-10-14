/*
    UTILITY & DEBUG FUNCTIONS
*/

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <string>

#include "common.hpp"

// Return a string with both the Allegro and the program version
std::string versionToString();

// Display in the left up corner the FPS counter
void displayFPS(ALLEGRO_FONT *font);

// Transfor a direction to degrees
double directionToDegrees(dir direction);

// Transform into an angle between (0, 360)
// Iterative, fast for values between (-720, +720)
double normalAngle(double angle);

#endif
