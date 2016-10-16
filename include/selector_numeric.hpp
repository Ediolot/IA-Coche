#ifndef SELECTOR_NUMERIC
#define SELECTOR_NUMERIC

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <string>
#include <vector>
#include "common.hpp"
#include "fonts.hpp"
#include "images.hpp"

class selector_numeric {

    private:

        ALLEGRO_FONT *font_;

        std::string label_;
        double value_;
        int max_;
        int min_;

        double x_;
        double y_;

        bool r_mouse_inside_;
        bool r_mouse_pressed_;
        bool r_mouse_realased_;

        bool l_mouse_inside_;
        bool l_mouse_pressed_;
        bool l_mouse_realased_;

        double last_mouse_z_;

    public:

        selector_numeric(const std::string &label, ALLEGRO_FONT *font, const int min, const int max);

        ~selector_numeric();

        void moveTo(const double x, const double y);

        void update();

        void draw() const;

        bool mouseOverArrow() const;

        void setLabel(const std::string &label);

        int getValue() const;
};

#endif
