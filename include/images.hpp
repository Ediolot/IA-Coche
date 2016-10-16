/*
    CREATE AND DESTROY GLOBAL VARIABLES FOR THE FONTS
    VARIABLES: font_name_size
*/

#ifndef FONTS_HPP
#define FONTS_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

///////////////// GLOBAL IMAGES ///////////////
extern ALLEGRO_BITMAP *arrow;
extern ALLEGRO_BITMAP *pause_disabled;
extern ALLEGRO_BITMAP *pause;
extern ALLEGRO_BITMAP *play_disabled;
extern ALLEGRO_BITMAP *play;
extern ALLEGRO_BITMAP *random;
extern ALLEGRO_BITMAP *restart;
extern ALLEGRO_BITMAP *step_disabled;
extern ALLEGRO_BITMAP *step;
extern ALLEGRO_BITMAP *tracking_disabled;
extern ALLEGRO_BITMAP *tracking;

///////////////// FONTS PATHS ////////////////
extern const char caviar_font_path[];
extern const char ubuntu_mono_font_path[];

///////////////// FUNCTIONS ///////////////////////
bool loadFonts();
void destroyFonts();

#endif
