#ifndef SCENE_HPP
#define SCENE_HPP

#include <allegro5/allegro.h>
#include "common.hpp"
#include "map.hpp"
#include "button.hpp"
#include "button_image.hpp"
#include "scrollbar.hpp"
#include "selector.hpp"
#include "selector_numeric.hpp"

class scene {

    const double default_animation_time_ = 0.2;

    private:

        map tile_map_;          // Tiles map
        double map_separation_; // Tiles map's separation from the borders of the window
        double screen_w_;
        double screen_h_;

        bool show_menu_;
        bool isplaying_;
        bool istracking_;

        bool esc_was_pressed_;

        // BUTTONS WITH IMAGES
        button restart_;
        button play_;
        button random_;
        button step_;
        button tracking_;

        // BUTTONS WITH TEXT
        button quit_;

        // LIST SELECTORS
        selector algorithm_;

        // NUMERIC SELECTORS
        selector_numeric width_;
        selector_numeric height_;

        // SCROLLBARS
        scrollbar speed_;
        scrollbar obstacles_;

    public:
        scene(const double screen_w, const double screen_h, const double map_separation);
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
        void drawSim();
};

#endif
