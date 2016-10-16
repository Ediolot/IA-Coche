#ifndef BUTTON_IMAGE
#define BUTTON_IMAGE

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "common.hpp"
#include "fonts.hpp"
#include <string>

class button_image {

    private:

        ALLEGRO_BITMAP *image_;

        double x_;
        double y_;
        double w_;
        double h_;
        double min_w_;
        double min_h_;

        bool mouse_inside_;
        bool mouse_pressed_;
        bool mouse_realased_;
        uint was_pressed_events_;

    public:

        button_image(ALLEGRO_BITMAP *image);

        ~button_image();

        void moveTo(const double x, const double y, const double w, const double h);

        void update();

        void draw();

        bool mouseOver() const;

        void setImage(ALLEGRO_BITMAP *image);

        bool wasPressed();
};

#endif
