#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "label.hpp"

class button : public label {

    private:

        double animation_time_;
        double line_size_;
        double last_time_called_;

    public:

        button(const std::string &text,
              ALLEGRO_BITMAP *img,
              ALLEGRO_FONT   *font  = nullptr,
              ALLEGRO_COLOR  *color = nullptr,
              const double animation_time = .0 );

        button(ALLEGRO_BITMAP *img,
              ALLEGRO_FONT   *font  = nullptr,
              ALLEGRO_COLOR  *color = nullptr);
              const double animation_time = .0 );

        button(const std::string &text,
              ALLEGRO_FONT  *font  = nullptr,
              ALLEGRO_COLOR *color = nullptr);
              const double animation_time = .0 );

        ~button();

        virtual void update();
        virtual void draw();
};

#endif
