#ifndef SCROLLBAR_HPP
#define SCROLLBAR_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "common.hpp"
#include "fonts.hpp"
#include <string>

class scrollbar {

    private:

        scroll type_;

        bool show_;

        double value_;

        double x_;
        double y_;
        double w_;
        double h_;

        double last_mouse_z_;

        bool mouse_inside_;
        bool scrolling_;

    public:

        scrollbar(const scroll type, const double value = 0);

        ~scrollbar();

        void moveTo(const double x, const double y, const double w, const double h);

        void update();

        void draw();

        double getValue() const;

        void setValue(const double value);

        void show();
        void hide();
};

#endif
