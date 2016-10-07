/*
    CREATE AND DESTROY GLOBAL VARIABLES FOR THE FONTS
    VARIABLES: font_name_size
*/

#ifndef FONTS_HPP
#define FONTS_HPP

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

///////////////// GLOBAL FONTS ///////////////
ALLEGRO_FONT *caviar_font_16;
ALLEGRO_FONT *caviar_font_24;

///////////////// FONTS PATHS ////////////////
char caviar_font_path[] = "fonts/CaviarDreams.ttf";

///////////////// LOAD ///////////////////////
bool loadFonts()
{
    caviar_font_16  = al_load_ttf_font(caviar_font_path, 16, 0);
    caviar_font_24  = al_load_ttf_font(caviar_font_path, 24, 0);

    return caviar_font_16 && caviar_font_24; // && ...
}

///////////////// DESTROY ///////////////////
void destroyFonts()
{
    al_destroy_font(caviar_font_16);
    al_destroy_font(caviar_font_24);
}

#endif
