
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include <string>
#include <cstdio>
#include <iostream>

#include "../include/common.hpp"
#include "../include/fonts.hpp"
#include "../include/utility.hpp"
#include "../include/scene.hpp"
#include "../include/mouse.hpp"
#include "../include/images.hpp"

////////////////////// MAIN ///////////////////////
int main(int argc, char *argv[])
{
    // ALLEGRO VARIABLES
    ALLEGRO_DISPLAY     *display      = nullptr;
    ALLEGRO_EVENT_QUEUE *event_queue  = nullptr;
    ALLEGRO_TIMER       *redraw_timer = nullptr;

    bool redraw = true;

    // INITIALIZE ALLEGRO
    if (!al_init()                  ||
        !al_init_primitives_addon() ||
        !al_init_font_addon()       ||
        !al_init_ttf_addon()        ||
        !al_install_keyboard()      ||
        !al_install_mouse()         ||
        !al_init_image_addon() )
    {
        std::cerr << "Failed to initialize Allegro!" << std::endl;
        return -1;
    }

    // INITIALIZE ALLEGRO VARIABLES
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    redraw_timer = al_create_timer(1.0 / FPS);
    display      = al_create_display(SCREEN_W, SCREEN_H);
    event_queue  = al_create_event_queue();

    if (!redraw_timer ||
        !display      ||
        !event_queue  ||
        !loadFonts()  ||
        !loadImages())
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
    al_register_event_source(event_queue, al_get_mouse_event_source());

    // VARIABLES
    scene main_scene(SCREEN_W, SCREEN_H, map_separation);

    // START REDRAW TIMER
    al_start_timer(redraw_timer);

    // SET DISPLAY AS CURRENT BITMAP
    al_set_target_bitmap(al_get_backbuffer(display));

    // MAIN LOOP
    while (!quit)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        switch (ev.type)
        {
            case ALLEGRO_EVENT_TIMER:               redraw = true; break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:       quit   = true; break;

            case ALLEGRO_EVENT_KEY_DOWN:            keysPress[ev.keyboard.keycode] = true;  break;
            case ALLEGRO_EVENT_KEY_UP:              keysPress[ev.keyboard.keycode] = false; break;

            case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY: mouse.updatePos(ev); mouse.intoScreen(); break;
            case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY: mouse.updatePos(ev); mouse.outoScreen(); break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:   mouse.press(ev);     break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:     mouse.realase(ev);   break;
            case ALLEGRO_EVENT_MOUSE_AXES:          mouse.updatePos(ev); break;

            case ALLEGRO_EVENT_DISPLAY_RESIZE:
                al_acknowledge_resize(display);
                main_scene.resize(ev.display.width, ev.display.height);
                break;

            default: break; // Unused event
        }

        // Update screen
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            main_scene.update();
            main_scene.draw();
            al_flip_display();
        }
    }

    // CLEAN UP
    al_destroy_timer(redraw_timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    destroyFonts();
    destroyImages();

    return 0;
}
