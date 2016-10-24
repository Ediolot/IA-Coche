#include "../include/colors.hpp"

///////////////// LOAD ///////////////////
ALLEGRO_COLOR PURE_WHITE;
ALLEGRO_COLOR PURE_BLACK;
ALLEGRO_COLOR BLACK;
ALLEGRO_COLOR ORANGE;
ALLEGRO_COLOR ORANGE_STRONG;
ALLEGRO_COLOR LIGHT_GRAY;
ALLEGRO_COLOR GRAY;
ALLEGRO_COLOR BACKGROUND_COLOR;
ALLEGRO_COLOR NEUTRAL_TILE_COLOR;
ALLEGRO_COLOR WATER_TILE_COLOR;

bool loadColors()
{
    PURE_WHITE =         al_map_rgb(255,255,255);
    PURE_BLACK =         al_map_rgb(  0,  0,  0);
    BLACK =              al_map_rgb( 15, 15, 15);
    ORANGE =             al_map_rgb(187,222, 251);
    ORANGE_STRONG =      al_map_rgb(255,150,  0);
    LIGHT_GRAY =         al_map_rgb(100,100,100);
    GRAY =               al_map_rgb( 26, 26, 26);
    BACKGROUND_COLOR =   al_map_rgb(226,230,235);
    NEUTRAL_TILE_COLOR = al_map_rgb( 63, 64, 65);
    WATER_TILE_COLOR =   al_map_rgb(200,100,50);

    return true;
}
