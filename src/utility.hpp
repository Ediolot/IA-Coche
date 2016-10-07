/*
    UTILITY & DEBUG FUNCTIONS
*/

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>

#include "common.hpp"

////////////////////////////////////////////////////////////////////////////////
/* Display in the left up corner the FPS counter */

void displayFPS(ALLEGRO_FONT *font)
{
    static double old_time = 0;
    double new_time = al_get_time();
    int fps = 1/(new_time - old_time);

    std::string stringFPS("FPS: "+std::to_string(fps));

    al_draw_text(font, PURE_WHITE, 10, 10,ALLEGRO_ALIGN_LEFT, stringFPS.c_str());

    old_time = new_time;
}

////////////////////////////////////////////////////////////////////////////////
/* Returns a string with both the Allegro and the program version */

std::string versionToString()
{
    uint32_t version_allg = al_get_allegro_version();
    std::string version_string("");

    int major =  version_allg >> 24;
    int minor = (version_allg >> 16) & 255;

    version_string += NAME+" ";
    version_string += std::to_string(VERSION_MAYOR)+"."+std::to_string(VERSION_MINOR)+" (" + STAGE + ") ";
    version_string += "[Allegro "+std::to_string(major) + "." + std::to_string(minor) + "]";

    return version_string;
}

#endif
