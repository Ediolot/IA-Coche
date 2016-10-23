#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include "label.hpp"
#include <vector>

class selector : public label {

    private:
        std::vector<std::string> list_;
        uint selected_;

        double biggest_item_w_;

        bool r_mouse_inside_;
        bool r_mouse_pressed_;
        bool r_mouse_realased_;

        bool l_mouse_inside_;
        bool l_mouse_pressed_;
        bool l_mouse_realased_;

        // NOTE onchange_ ?

    public:

        selector(const std::vector<std::string>& list
                 const std::string &text,
                 ALLEGRO_BITMAP *img,
                 ALLEGRO_FONT   *font  = nullptr,
                 ALLEGRO_COLOR  *color = nullptr);

        selector(const std::vector<std::string>& list
                 ALLEGRO_BITMAP *img,
                 ALLEGRO_FONT   *font  = nullptr,
                 ALLEGRO_COLOR  *color = nullptr);

        selector(const std::vector<std::string>& list
                 const std::string &text,
                 ALLEGRO_FONT  *font  = nullptr,
                 ALLEGRO_COLOR *color = nullptr);

        ~selector();

        virtual void resize(const double x, const double y, const double w = 0, const double h = 0);
        virtual void update();
        virtual void draw();

        uint getSelectedIndex() const;
};

#endif
