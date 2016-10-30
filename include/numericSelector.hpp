#ifndef SELECTOR_NUMERIC_HPP
#define SELECTOR_NUMERIC_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <string>
#include <vector>
#include "common.hpp"
#include "fonts.hpp"
#include "images.hpp"
#include "label.hpp"

class numericSelector {

    protected:

        const double arrows_margin = 40;

        ALLEGRO_COLOR color_;
        ALLEGRO_FONT *font_;
        label label_;

        bool show_;

        double x_;
        double y_;
        double w_;
        double h_;

        double selector_x_;
        double selector_text_y_;
        double selector_img_y_;

        double text_h_;
        double img_w_;
        double img_h_;

        int max_;
        int min_;
        int value_;

        dir v_aling_;
        dir h_aling_;

        uint press_state_l_;
        uint press_state_r_;

        bool mouse_over_;
        double last_mouse_z_;

    public:

        numericSelector(const std::string &text,
                        ALLEGRO_BITMAP *img,
                        ALLEGRO_FONT   *font,
                        ALLEGRO_COLOR  color,
                        int min = -999,
                        int max = +999,
                        int val = 0);

        numericSelector(ALLEGRO_BITMAP *img,
                        int min = -999,
                        int max = +999,
                        int val = 0);

        numericSelector(const std::string &text,
                        ALLEGRO_FONT   *font,
                        ALLEGRO_COLOR  color,
                        int min = -999,
                        int max = +999,
                        int val = 0);

        ~numericSelector();

        virtual void resize(const double x, const double y, const double w = 0, const double h = 0);

        virtual void update();

        virtual void draw();

        int getValue() const;

        /* Mouse was over in the last update */
        bool mouseOver();

        void setText(const std::string &text);
        void setImg(ALLEGRO_BITMAP *img);
        void setFont(ALLEGRO_FONT *font);
        void setColor(ALLEGRO_COLOR color);
        void setVerticalTextAling(const dir v_aling);
        void setHorizontalTextAling(const dir h_aling);

        virtual double getMinWidth() const;
        virtual double getMinHeight() const;

        void show(bool show);
        void hide();
};

#endif
