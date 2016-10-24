/*
    TYPES AND COMMON DEFINITIONS
*/

#ifndef COMMON_HPP
#define COMMON_HPP

#include <allegro5/allegro.h>
#include <string>
#include "mouse.hpp"
#include "colors.hpp"

typedef unsigned int uint;

///////////////// QUIT /////////////////

extern bool quit;

////////////////// KEYS ////////////////

extern bool keysPress[ALLEGRO_KEY_MAX];

///////////////// MOUSE ////////////////

extern _mouse mouse;

///////////////// VERSION ////////////////

const uint VERSION_MAYOR = 0;
const uint VERSION_MINOR = 1;
const std::string STAGE  = "Alpha";
const std::string NAME   = "IA";

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

///////////// SCROLLBAR TYPE /////////////

enum scroll {
    VERTICAL,
    HORIZONTAL
};

#endif
