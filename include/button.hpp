#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "common.hpp"
#include "fonts.hpp"
#include "label"
#include <string>

class button : public label {

    private:

        double animation_time_;
        double line_size_;
        double last_time_called_;

    public:

        button(const std::string &label, ALLEGRO_FONT *font, const double animation_time);

        ~button();

        void resize(const double x, const double y, const double w = 0, const double h = 0);

        void update();

        void draw();
};

#endif
