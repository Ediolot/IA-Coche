#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include "numericSelector.hpp"
#include <vector>

class selector : public numericSelector {

    private:

        std::vector<std::string> list_;
        double biggest_item_w_;

    public:

        selector(const std::vector<std::string>& list,
                 const std::string &text,
                 ALLEGRO_BITMAP *img,
                 ALLEGRO_FONT   *font,
                 ALLEGRO_COLOR  color);

        selector(const std::vector<std::string>& list,
                 ALLEGRO_BITMAP *img);

        selector(const std::vector<std::string>& list,
                 const std::string &text,
                 ALLEGRO_FONT  *font,
                 ALLEGRO_COLOR color);

        ~selector();

        virtual void draw();
        virtual double getMinWidth() const;
};

#endif
