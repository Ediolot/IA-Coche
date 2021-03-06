#ifndef LABEL_HPP
#define LABEL_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <string>
#include <functional>
#include "common.hpp"
#include "fonts.hpp"
#include "images.hpp"

class label {

    protected:

        ALLEGRO_COLOR color_;
        ALLEGRO_FONT *font_;
        ALLEGRO_BITMAP *img_;
        std::string text_;

        bool show_;

        double x_;
        double y_;
        double w_;
        double h_;

        double text_x_;
        double text_y_;
        double img_x_;
        double img_y_;

        double text_w_;
        double text_h_;
        double img_w_;
        double img_h_;

        dir v_aling_;
        dir h_aling_;

        bool mouse_over_;
        uint press_state_;
        uint clicks_;

    public:

        label(const std::string &text,
              ALLEGRO_BITMAP *img,
              ALLEGRO_COLOR color,
              ALLEGRO_FONT *font);

        label(ALLEGRO_BITMAP *img);

        label(const std::string &text,
              ALLEGRO_COLOR color,
              ALLEGRO_FONT *font);

        ~label();

        virtual void resize(const double x, const double y, const double w = 0, const double h = 0);
        virtual void update();
        virtual void draw();

        /* Mouse was over in the last update */
        bool mouseOver();
        /* Clicked on the last update */
        bool mouseClicked();

        void setText(const std::string &text);
        void setImg(ALLEGRO_BITMAP *img);
        void setFont(ALLEGRO_FONT *font);
        void setColor(ALLEGRO_COLOR color);
        void setVerticalTextAling(const dir v_aling);
        void setHorizontalTextAling(const dir h_aling);

        double getMinWidth() const;
        double getMinHeight() const;

        void show(bool show = true);
        void hide();
};

#endif
