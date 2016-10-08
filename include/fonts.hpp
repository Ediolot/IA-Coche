/*
    CREATE AND DESTROY GLOBAL VARIABLES FOR THE FONTS
    VARIABLES: font_name_size
*/

#ifndef FONTS_HPP
#define FONTS_HPP

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

///////////////// GLOBAL FONTS ///////////////
extern ALLEGRO_FONT *caviar_font_8;
extern ALLEGRO_FONT *caviar_font_16;
extern ALLEGRO_FONT *caviar_font_24;

///////////////// FONTS PATHS ////////////////
extern const char caviar_font_path[];

///////////////// FUNCTIONS ///////////////////////
bool loadFonts();
void destroyFonts();

#endif
