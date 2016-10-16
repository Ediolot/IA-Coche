/*
    TYPES AND COMMON DEFINITIONS
*/

#ifndef COMMON_HPP
#define COMMON_HPP

#include <allegro5/allegro.h>
#include <string>
#include "mouse.hpp"

typedef unsigned int uint;

///////////////// MOUSE ////////////////

extern _mouse mouse;

///////////////// VERSION ////////////////

const uint VERSION_MAYOR = 0;
const uint VERSION_MINOR = 1;
const std::string STAGE  = "Alpha";
const std::string NAME   = "Castle Square";

///////////////// DIRECTIONS ////////////////

enum dir {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
    CENTER
};

/////////////// TILE TYPES //////////////

enum tileType {
    NEUTRAL,
    WATER
};

/////////////// MEASURE UNITS /////////////

enum units {
    PX,
    PERCENT
};

///////////////// COLORS /////////////////
#define PURE_WHITE          al_map_rgb(255,255,255)
#define PURE_BLACK          al_map_rgb(  0,  0,  0)
#define BLACK               al_map_rgb( 15, 15, 15)
#define ORANGE              al_map_rgb(187,222, 251)
#define ORANGE_STRONG       al_map_rgb(255,150,  0)
#define LIGHT_GRAY          al_map_rgb(100,100,100)
#define GRAY                al_map_rgb( 26, 26, 26)
#define BACKGROUND_COLOR    al_map_rgb(226,230,235)
#define NEUTRAL_TILE_COLOR  al_map_rgb( 63, 64, 65)
#define WATER_TILE_COLOR    al_map_rgb(  0,137,123)

#endif
