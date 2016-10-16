/*
    CREATE AND DESTROY GLOBAL VARIABLES FOR THE FONTS
    VARIABLES: font_name_size
*/

#ifndef IMAGES_HPP
#define IMAGES_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

///////////////// GLOBAL IMAGES ///////////////
extern ALLEGRO_BITMAP *arrow_image;
extern ALLEGRO_BITMAP *pause_disabled_image;
extern ALLEGRO_BITMAP *pause_image;
extern ALLEGRO_BITMAP *play_disabled_image;
extern ALLEGRO_BITMAP *play_image;
extern ALLEGRO_BITMAP *random_image;
extern ALLEGRO_BITMAP *restart_image;
extern ALLEGRO_BITMAP *step_disabled_image;
extern ALLEGRO_BITMAP *step_image;
extern ALLEGRO_BITMAP *tracking_disabled_image;
extern ALLEGRO_BITMAP *tracking_image;

///////////////// IMAGES PATHS ////////////////
extern const char arrow_path[];
extern const char pause_disabled_path[];
extern const char pause_path[];
extern const char play_disabled_path[];
extern const char play_path[];
extern const char random_path[];
extern const char restart_path[];
extern const char step_disabled_path[];
extern const char step_path[];
extern const char tracking_disabled_path[];
extern const char tracking_path[];

///////////////// FUNCTIONS ///////////////////////
bool loadImages();
void destroyImages();

#endif
