#ifndef LABEL_HPP
#define LABEL_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <functional>
#include "common.hpp"
#include "fonts.hpp"
#include "images.hpp"

//TODO mover a common
enum hAling {
    LEFT, CENTER, RIGHT
}

enum vAling {
    TOP, CENTER, BOT
}

class label {

    private:

        ALLEGRO_COLOR *color_;
        ALLEGRO_FONT *font_;
        ALLEGRO_BITMAP *img_;
        std::string label_;

        double x_;
        double y_;
        double w_;
        double h_;

        bool mouse_over_;
        uint press_state_;

        double label_w_;
        double label_h_;
        double img_w_;
        double img_h_;

        vAling v_aling_;
        hAling h_aling_;

        void (*onclick_)();
        void (*onmouseover_)();

    public:

        label(const std::string &label,
              ALLEGRO_BITMAP *img,
              ALLEGRO_FONT   *font  = nullptr,
              ALLEGRO_COLOR  *color = nullptr);

        label(ALLEGRO_BITMAP *img,
              ALLEGRO_FONT   *font  = nullptr,
              ALLEGRO_COLOR  *color = nullptr);

        label(const std::string &label,
              ALLEGRO_FONT  *font  = nullptr,
              ALLEGRO_COLOR *color = nullptr)

        ~label();

        virtual void resize(const double x, const double y, const double w = 0, const double h = 0);
        virtual void update();
        virtual void draw();

        /* Executes function when a click is detected in the object area */
        void onMouseClick(const std::function<void()> &f);
        /* Executes function when mouse enters the object area */
        void onMouseOver(const std::function<void()> &f);

        /* Mouse was over in the last update */
        bool mouseOver();
        /* Clicked on the last update */
        bool mouseClicked();

        void setLabel(const std::string &label);
        void setImg(ALLEGRO_BITMAP *img);
        void setFont(ALLEGRO_FONT *font);
        void setColor(ALLEGRO_FONT *color);
};

#endif
