#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <string>
#include <vector>
#include "common.hpp"
#include "fonts.hpp"
#include "images.hpp"

class selector {

    private:

        ALLEGRO_FONT *font_;

        std::string label_;
        std::vector<std::string> list_;
        uint selected_;

        double x_;
        double y_;
        double w_;

        bool r_mouse_inside_;
        bool r_mouse_pressed_;
        bool r_mouse_realased_;

        bool l_mouse_inside_;
        bool l_mouse_pressed_;
        bool l_mouse_realased_;

    public:

        selector(const std::string &label, ALLEGRO_FONT *font, const std::vector<std::string>& list);

        ~selector();

        void moveTo(const double x, const double y);

        void update();

        void draw() const;

        bool mouseOverArrow() const;

        void setLabel(const std::string &label);

        uint getSelectedIndex() const;
};

#endif
