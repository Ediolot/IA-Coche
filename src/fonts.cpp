#include "../include/fonts.hpp"

///////////////// GLOBAL FONTS ///////////////
ALLEGRO_FONT *caviar_font_8 = nullptr;
ALLEGRO_FONT *caviar_font_16 = nullptr;
ALLEGRO_FONT *caviar_font_24 = nullptr;

///////////////// FONTS PATHS ////////////////

const char caviar_font_path[] = "fonts/CaviarDreams.ttf";

///////////////// LOAD ///////////////////
bool loadFonts()
{
    caviar_font_8  = al_load_ttf_font(caviar_font_path, 8, 0);
    caviar_font_16  = al_load_ttf_font(caviar_font_path, 16, 0);
    caviar_font_24  = al_load_ttf_font(caviar_font_path, 24, 0);

    return caviar_font_8 && caviar_font_16 && caviar_font_24; // && ...
}

///////////////// DESTROY ///////////////////
void destroyFonts()
{
    al_destroy_font(caviar_font_8);
    al_destroy_font(caviar_font_16);
    al_destroy_font(caviar_font_24);
}
