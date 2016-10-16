
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "common.hpp"
#include "fonts.hpp"
#include <string>
#include <vector>

class selector {

    private:

        std::string label_;
        std::vector<std::string> list_;
        uint selected_;

        ALLEGRO_BITMAP *arrow_;

        double x_;
        double y_;
        double w_;

        bool r_mouse_inside_;
        bool r_mouse_pressed_;
        bool r_mouse_realased_;

        bool l_mouse_inside_;
        bool l_mouse_pressed_;
        bool l_mouse_realased_;

    public:

        selector(const std::string &label, const std::vector<std::string>& list, const std::string& arrow_path);

        ~selector();

        void moveTo(const double x, const double y);

        void update();

        void draw();

        bool mouseOverArrow() const;

        void setLabel(const std::string &label);

        uint getSelectedIndex() const;
};
