
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <cstdio>
#include <string>
#include <iostream>

#include "common.hpp"
#include "utility.hpp"
#include "map.hpp"

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;

// g++ src/*.cpp -std=c++11 -Wall -o bin/a.out $(pkg-config --libs --static allegro-static-5 allegro_ttf-static-5 allegro_font-static-5 allegro_primitives-static-5) && ./bin/a.out

int main(int argc, char *argv[])
{
    ALLEGRO_DISPLAY *display = nullptr;
    ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
    ALLEGRO_TIMER *FPStimer = nullptr;
    ALLEGRO_FONT *caviarFont = nullptr;

    bool redraw = true;
    bool quit = false;

    if (!al_init())
    {
        std::cerr << "failed to initialize allegro!" << std::endl;
        return -1;
    }

    if (!al_init_primitives_addon())
    {
        std::cerr << "failed to initialize primitives!" << std::endl;
        return -1;
    }

    if (!al_init_font_addon() || !al_init_ttf_addon())
    {
        std::cerr << "failed to initialize fonts!" << std::endl;
        return -1;
    }

    FPStimer = al_create_timer(1.0 / FPS);
    if (!FPStimer)
    {
        std::cerr << "failed to create timer!" << std::endl;
        return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display)
    {
        std::cerr << "failed to create display!" << std::endl;
        al_destroy_timer(FPStimer);
        return -1;
    }

    event_queue = al_create_event_queue();
    if (!event_queue)
    {
        std::cerr << "failed to create event_queue!" << std::endl;
        al_destroy_display(display);
        al_destroy_timer(FPStimer);
        return -1;
    }

    caviarFont = al_load_ttf_font("fonts/CaviarDreams.ttf", 16, 0);
    if (!caviarFont)
    {
        std::cerr << "failed to create caviarFont!" << std::endl;
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(FPStimer));

    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(BLACK);
    al_flip_display();

    al_start_timer(FPStimer);

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
            map mymap;
            al_clear_to_color(BLACK);
            displayFPS(caviarFont);
            mymap.draw();
            al_flip_display();
        }
    }

    al_destroy_timer(FPStimer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
