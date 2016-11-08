#include "../include/utility.hpp"

////////////////////////////////////////////////////////////////////////////////

void displayFPS(ALLEGRO_FONT *font)
{
    static uint iteration = 0;
    static double elapsed = 0;
    static double old_time = 0;
    static int fps = 0;

    double new_time = al_get_time();

    if (++iteration > 20)
    {
        fps = 20/elapsed;
        iteration = 0;
        elapsed = 0;
    }
    else
        elapsed += (new_time - old_time);

    std::string stringFPS("FPS: "+std::to_string(fps));
    al_draw_text(font, BLACK, 10, 10,ALLEGRO_ALIGN_LEFT, stringFPS.c_str());

    old_time = new_time;
}

////////////////////////////////////////////////////////////////////////////////

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
