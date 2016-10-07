/*
    TYPES AND COMMON DEFINITIONS
*/

#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>

typedef unsigned int uint;

///////////////// VERSION ////////////////
const uint VERSION_MAYOR = 0;
const uint VERSION_MINOR = 1;
const std::string STAGE  = "Alpha";
const std::string NAME   = "Castle Square";

///////////////// COLORS /////////////////
#define PURE_WHITE          al_map_rgb(255,255,255)
#define PURE_BLACK          al_map_rgb(  0,  0,  0)
#define BLACK               al_map_rgb( 15, 15, 15)
#define ORANGE              al_map_rgb(244,188, 66)
#define BACKGROUND_COLOR    al_map_rgb(226,230,235)
#define NEUTRAL_TILE_COLOR  al_map_rgb( 63, 64, 65)

///////////////// POINT //////////////////
struct point
{
    double x;
    double y;

    void set(double x1, double y1)
    {
        x = x1;
        y = y1;
    }
};

#endif
