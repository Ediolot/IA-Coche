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
#include "label.hpp"

class numericSelector {

    protected:

        ALLEGRO_COLOR *color_;
        ALLEGRO_FONT *font_;

        label label_;

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

        uint press_state_left_;
        uint press_state_right_;

        // NOTE onchange_ ?

        bool mouse_over_;
        void (*onmouseover_)();

        double last_mouse_z_;

    public:

        numericSelector(const std::string &text,
                        ALLEGRO_BITMAP *img,
                        ALLEGRO_FONT   *font  = nullptr,
                        ALLEGRO_COLOR  *color = nullptr,
                        int min = -999,
                        int max = +999,
                        int val = 0);

        numericSelector(ALLEGRO_BITMAP *img,
                        ALLEGRO_FONT   *font  = nullptr,
                        ALLEGRO_COLOR  *color = nullptr,
                        int min = -999,
                        int max = +999,
                        int val = 0);

        numericSelector(const std::string &text,
                        ALLEGRO_FONT   *font  = nullptr,
                        ALLEGRO_COLOR  *color = nullptr,
                        int min = -999,
                        int max = +999,
                        int val = 0);

        ~numericSelector();

        virtual void resize(const double x, const double y, const double w = 0, const double h = 0);

        virtual void update();

        virtual void draw();

        int getValue() const;

        /* Executes function when mouse enters the object area */
        void onMouseOver(const std::function<void()> &f);

        /* Mouse was over in the last update */
        bool mouseOver();

        void setText(const std::string &text);
        void setImg(ALLEGRO_BITMAP *img);
        void setFont(ALLEGRO_FONT *font);
        void setColor(ALLEGRO_FONT *color);
        void setVerticalTextAling(const dir v_aling);
        void setHorizontalTextAling(const dir h_aling);

        virtual double getMinWidth() const;
        virtual double getMinHeight() const;
};

#endif
