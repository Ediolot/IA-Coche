/*
    TYPES AND COMMON DEFINITIONS
*/

#ifndef COMMON_HPP
#define COMMON_HPP

#include <allegro5/allegro.h>
#include <string>
#include "mouse.hpp"
#include "config.hpp"

typedef unsigned int uint;

///////////////// QUIT /////////////////

extern bool quit;

////////////////// KEYS ////////////////

extern bool keysPress[ALLEGRO_KEY_MAX];

///////////////// MOUSE ////////////////

extern _mouse mouse;

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
#define WATER_TILE_COLOR    al_map_rgb(200,100,50)

#endif
