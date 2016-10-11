
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
const bool   accumulative_rivers = false;
const double FPS      = 90;
const uint   mapsize  = 15;
const uint   rivers   = 2;
const int    SCREEN_W = 800;
const int    SCREEN_H = 800;

////////////////// SCENE RENDER ///////////////////
void renderScene(const map &tileMap)
{
    displayFPS(caviar_font_16);
    std::cout << (SCREEN_W>SCREEN_H ? SCREEN_H*0.8 : SCREEN_W*0.8) << std::endl;
    tileMap.draw(SCREEN_W/2, SCREEN_H/2, SCREEN_W>SCREEN_H ? SCREEN_H*0.8 : SCREEN_W*0.8);
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

    // VARIABLES
    map tileMap(mapsize);

    tileMap.generateScenario(rivers,mapsize,accumulative_rivers);

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
            default: break; // Unused event
        }

        // Update screen
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(BACKGROUND_COLOR); // Clear
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
