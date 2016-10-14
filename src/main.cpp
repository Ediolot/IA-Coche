
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <string>
#include <cstdio>
#include <iostream>

#include "../include/common.hpp"
#include "../include/fonts.hpp"
#include "../include/utility.hpp"
#include "../include/scene.hpp"

///////////////// DEFAULT OPTIONS /////////////////
bool keysPress[ALLEGRO_KEY_MAX] = {false};

///////////////// DEFAULT OPTIONS /////////////////
const bool   accumulative_rivers = false;
const double FPS         = 90;
const double scrollSpeed = 0.08;
const double border      = 0.95;
const double separation  = 0.06;
const uint   mapsize     = 20;
const uint   rivers      = 2;
const int    SCREEN_W    = 800;
const int    SCREEN_H    = 700;

////////////////// SCENE RENDER ///////////////////
void updateMovement(scene &s)
{
    if (keysPress[ALLEGRO_KEY_W]) s.moveY(+scrollSpeed*FPS);
    if (keysPress[ALLEGRO_KEY_S]) s.moveY(-scrollSpeed*FPS);
    if (keysPress[ALLEGRO_KEY_A]) s.moveX(+scrollSpeed*FPS);
    if (keysPress[ALLEGRO_KEY_D]) s.moveX(-scrollSpeed*FPS);
}

////////////////////// MAIN ///////////////////////
int main(int argc, char *argv[])
{
    // ALLEGRO VARIABLES
    ALLEGRO_DISPLAY     *display      = nullptr;
    ALLEGRO_EVENT_QUEUE *event_queue  = nullptr;
    ALLEGRO_TIMER       *redraw_timer = nullptr;

    bool redraw = true;
    bool quit   = false;

    // INITIALIZE ALLEGRO
    if (!al_init()                  ||
        !al_init_primitives_addon() ||
        !al_init_font_addon()       ||
        !al_init_ttf_addon()        ||
        !al_install_keyboard())
    {
        std::cerr << "Failed to initialize Allegro!" << std::endl;
        return -1;
    }

    // INITIALIZE ALLEGRO VARIABLES
    redraw_timer = al_create_timer(1.0 / FPS);
    display      = al_create_display(SCREEN_W, SCREEN_H);
    event_queue  = al_create_event_queue();

    if (!redraw_timer ||
        !display      ||
        !event_queue  ||
        !loadFonts())
    {
        std::cerr << "Failed to create variables!" << std::endl;
        return -1;
    }

    // DISPLAY VERSION
    std::cout << versionToString() << std::endl;

    // REGISTER EVENTS
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(redraw_timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // VARIABLES
    scene main_scene(SCREEN_W, SCREEN_H, mapsize, 0.06);

    main_scene.generate(rivers, mapsize, accumulative_rivers);

    // START REDRAW TIMER
    al_start_timer(redraw_timer);

    // MAIN LOOP
    while (!quit)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        switch (ev.type)
        {
            case ALLEGRO_EVENT_TIMER:           redraw = true; break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:   quit   = true; break;
            case ALLEGRO_EVENT_KEY_DOWN:        keysPress[ev.keyboard.keycode] = true;  break;
            case ALLEGRO_EVENT_KEY_UP:          keysPress[ev.keyboard.keycode] = false; break;
            default: break; // Unused event
        }

        if (keysPress[ALLEGRO_KEY_ESCAPE])
            quit = true;

        // Update screen
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

            updateMovement(main_scene);
            main_scene.draw();

            std::string stringFPS("Triangles: "+std::to_string(triangles_global));
            al_draw_text(caviar_font_16, BLACK, 10, 40,ALLEGRO_ALIGN_LEFT, stringFPS.c_str());

            displayFPS(caviar_font_16);
            al_flip_display();
        }
    }

    // CLEAN UP
    al_destroy_timer(redraw_timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    destroyFonts();

    return 0;
}
