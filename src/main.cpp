
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <string>
#include <cstdio>
#include <iostream>

#include "common.hpp"
#include "utility.hpp"
#include "map.hpp"

///////////////// DEFAULT OPTIONS /////////////////
const double FPS = 60;
const int SCREEN_W = 800;
const int SCREEN_H = 800;

////////////////////// MAIN ///////////////////////
int main(int argc, char *argv[])
{
    ALLEGRO_DISPLAY     *display      = nullptr;
    ALLEGRO_EVENT_QUEUE *event_queue  = nullptr;
    ALLEGRO_TIMER       *redraw_timer = nullptr;
    ALLEGRO_FONT        *caviar_font  = nullptr;

    bool redraw = true;
    bool quit   = false;

    if (!al_init() ||
        !al_init_primitives_addon() ||
        !al_init_font_addon() ||
        !al_init_ttf_addon())
    {
        std::cerr << "Failed to initialize Allegro!" << std::endl;
        return -1;
    }

    std::cout << versionToString() << std::endl;

    redraw_timer = al_create_timer(1.0 / FPS);
    display      = al_create_display(SCREEN_W, SCREEN_H);
    event_queue  = al_create_event_queue();
    caviar_font  = al_load_ttf_font("fonts/CaviarDreams.ttf", 16, 0);

    if (!redraw_timer || !display || !event_queue || !caviar_font)
    {
        std::cerr << "Failed to create variables!" << std::endl;
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(redraw_timer));

    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(BLACK);
    al_flip_display();

    al_start_timer(redraw_timer);

    map mymap(10, SCREEN_W, SCREEN_H);
    while(!quit)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        switch (ev.type)
        {
            case ALLEGRO_EVENT_TIMER: redraw = true; break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE: quit = true; break;
            default: std::cout << "Unregistered event fired: " << ev.type << std::endl;
        }

        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(BLACK);
            displayFPS(caviar_font);
            mymap.draw();
            al_flip_display();
        }
    }

    al_destroy_timer(redraw_timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
