
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "common.hpp"
#include "fonts.hpp"
#include <string>

class button {

    private:

        std::string label_;

        double x_;
        double y_;
        double w_;
        double h_;
        double min_w_;
        double min_h_;

        bool mouse_inside_;
        bool mouse_pressed_;
        uint was_pressed_events_;

        double animation_time_;
        double line_size_;
        double last_time_called_;

    public:

        button(const std::string &label, const double animation_time);

        ~button();

        void moveTo(const double x, const double y, const double w, const double h);

        void update();

        void draw();

        bool mouseOver() const;

        void setLabel(const std::string &label);

        bool wasPressed();
};
