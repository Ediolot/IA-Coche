
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
#include "../include/map.hpp"

///////////////// DEFAULT OPTIONS /////////////////
const double FPS      = 60;
const uint   mapsize  = 10;
const int    SCREEN_W = 800;
const int    SCREEN_H = 800;

////////////////// SCENE RENDER ///////////////////

void renderScene(const map &tileMap)
{
    al_clear_to_color(BLACK); // Clear
    displayFPS(caviar_font_16);
    tileMap.draw();
}

////////////////////// MAIN ///////////////////////
int main(int argc, char *argv[])
{

    // VARIABLES
    map tileMap(mapsize, SCREEN_W, SCREEN_H);

    ALLEGRO_DISPLAY     *display      = nullptr;
    ALLEGRO_EVENT_QUEUE *event_queue  = nullptr;
    ALLEGRO_TIMER       *redraw_timer = nullptr;

    bool redraw = true;
    bool quit   = false;

    // INITIALIZE ALLEGRO
    if (!al_init()                  ||
        !al_init_primitives_addon() ||
        !al_init_font_addon()       ||
        !al_init_ttf_addon())
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

    // START REDRAW TIMER
    al_start_timer(redraw_timer);

    // MAIN LOOP
    while(!quit)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        switch (ev.type)
        {
            case ALLEGRO_EVENT_TIMER:         redraw = true; break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE: quit   = true; break;

            default: std::cout << "Unregistered event fired: " << ev.type << std::endl; // Unused event
        }

        // Update screen
        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            renderScene(tileMap);
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
