#include "../include/images.hpp"

/* http://opengameart.org/content/pixel-platformer-tile-set */

///////////////// GLOBAL FONTS ///////////////
ALLEGRO_BITMAP *floor_image = nullptr;
ALLEGRO_BITMAP *wall_image = nullptr;
ALLEGRO_BITMAP *arrow_image = nullptr;
ALLEGRO_BITMAP *pause_disabled_image = nullptr;
ALLEGRO_BITMAP *pause_image = nullptr;
ALLEGRO_BITMAP *play_disabled_image = nullptr;
ALLEGRO_BITMAP *play_image = nullptr;
ALLEGRO_BITMAP *random_image = nullptr;
ALLEGRO_BITMAP *restart_image = nullptr;
ALLEGRO_BITMAP *step_disabled_image = nullptr;
ALLEGRO_BITMAP *step_image = nullptr;
ALLEGRO_BITMAP *tracking_disabled_image = nullptr;
ALLEGRO_BITMAP *tracking_image = nullptr;

///////////////// FONTS PATHS ////////////////
const char arrow_path[]             = "images/larrow.png";
const char floor_path[]             = "images/floor.png";
const char wall_path[]              = "images/wall.png";
const char pause_disabled_path[]    = "images/pause_disabled.png";
const char pause_path[]             = "images/pause.png";
const char play_disabled_path[]     = "images/play_disabled.png";
const char play_path[]              = "images/play.png";
const char random_path[]            = "images/random.png";
const char restart_path[]           = "images/restart.png";
const char step_disabled_path[]     = "images/step_disabled.png";
const char step_path[]              = "images/step.png";
const char tracking_disabled_path[] = "images/tracking_disabled.png";
const char tracking_path[]          = "images/tracking.png";

///////////////// LOAD ///////////////////

bool loadImages()
{
    arrow_image             = al_load_bitmap(arrow_path);
    floor_image             = al_load_bitmap(floor_path);
    wall_image              = al_load_bitmap(wall_path);
    pause_disabled_image    = al_load_bitmap(pause_disabled_path);
    pause_image             = al_load_bitmap(pause_path);
    play_disabled_image     = al_load_bitmap(play_disabled_path);
    play_image              = al_load_bitmap(play_path);
    random_image            = al_load_bitmap(random_path);
    restart_image           = al_load_bitmap(restart_path);
    step_disabled_image     = al_load_bitmap(step_disabled_path);
    step_image              = al_load_bitmap(step_path);
    tracking_disabled_image = al_load_bitmap(tracking_disabled_path);
    tracking_image          = al_load_bitmap(tracking_path);

    return arrow_image             &&
           floor_image             &&
           wall_image              &&
           pause_disabled_image    &&
           pause_image             &&
           play_disabled_image     &&
           play_image              &&
           random_image            &&
           restart_image           &&
           step_disabled_image     &&
           step_image              &&
           tracking_disabled_image &&
           tracking_image;
}

///////////////// DESTROY ///////////////////
void destroyImages()
{
    al_destroy_bitmap(arrow_image);
    al_destroy_bitmap(floor_image);
    al_destroy_bitmap(wall_image);
    al_destroy_bitmap(pause_disabled_image);
    al_destroy_bitmap(pause_image);
    al_destroy_bitmap(play_disabled_image);
    al_destroy_bitmap(play_image);
    al_destroy_bitmap(random_image);
    al_destroy_bitmap(restart_image);
    al_destroy_bitmap(step_disabled_image);
    al_destroy_bitmap(step_image);
    al_destroy_bitmap(tracking_disabled_image);
    al_destroy_bitmap(tracking_image);
}
