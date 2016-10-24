#ifndef SCENE_HPP
#define SCENE_HPP

#include <allegro5/allegro.h>
#include "common.hpp"
#include "map.hpp"
#include "button.hpp"
#include "scrollbar.hpp"
#include "selector.hpp"
#include "numericSelector.hpp"

class scene {

    const double default_animation_time_ = 0.2;

    private:

        map tile_map_;          // Tiles map
        double map_separation_; // Tiles map's separation from the borders of the window
        double screen_w_;
        double screen_h_;
        double inc_x_;
        double inc_y_;
        double zoom_;

        double last_mouse_z_;

        bool show_menu_;
        bool isplaying_;
        bool istracking_;

        bool esc_was_pressed_;

        // BUTTONS
        button restart_;
        button play_;
        button random_;
        button step_;
        button tracking_;
        button quit_;

        // LIST SELECTORS
        selector algorithm_;

        // NUMERIC SELECTORS
        numericSelector width_;
        numericSelector height_;

        // SCROLLBARS
        scrollbar speed_;
        scrollbar obstacles_;

    public:
        scene(const double screen_w, const double screen_h, const double tiles_separation, const double map_separation);
        virtual ~scene();

        // Dibuja los elementos de la escena
        void draw();

        // Mueve la escena en x o y
        void moveX(const double x);
        void moveY(const double y);

        void resize(const double w, const double h);
        void update();

    private:
        void drawMenu();
        void drawSimMenu(const uint triangles);
};

#endif
