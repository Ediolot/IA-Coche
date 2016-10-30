#ifndef SCROLLBAR_HPP
#define SCROLLBAR_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "common.hpp"
#include "fonts.hpp"
#include <string>

class scrollbar {

    /* NOTE Not updated, but good enough to work */

    private:

        bool show_;

        scroll type_;
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

        void resize(const double x, const double y, const double w, const double h);

        void update();

        void draw();

        double getValue() const;

        void setValue(const double value);

        void show(bool show);
        void hide();
};

#endif
