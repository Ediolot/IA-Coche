#include "../include/selector_numeric.hpp"

selector_numeric::selector_numeric(const std::string &label, ALLEGRO_FONT *font, const int min, const int max):
    font_(font),
    label_(label),
    value_(min),
    max_(max),
    min_(min),
    x_(0),
    y_(0),
    r_mouse_inside_(false),
    r_mouse_pressed_(false),
    r_mouse_realased_(false),
    l_mouse_inside_(false),
    l_mouse_pressed_(false),
    l_mouse_realased_(false),
    last_mouse_z_(0)
{}

selector_numeric::~selector_numeric()
{}

void selector_numeric::moveTo(const double x, const double y)
{
    x_ = x;
    y_ = y;
}

void selector_numeric::update()
{
    double labelw = al_get_text_width(font_, label_.c_str());
    double lw = al_get_bitmap_width(arrow_image);
    double w = al_get_text_width(font_, std::to_string(int(value_)).c_str());

    l_mouse_inside_ = mouse.insideBox(x_+labelw+10, y_-5, x_+labelw+lw+40, y_+30);
    r_mouse_inside_ = mouse.insideBox(x_+labelw+lw+w+50, y_-5, x_+labelw+lw+w+80, y_+30);

    if (!l_mouse_inside_)
        l_mouse_realased_ = l_mouse_pressed_ = false;

    else
    {
        if (!mouse.isPressed(1))
            l_mouse_realased_ = true;

        if (mouse.isPressed(1) && l_mouse_realased_)
        {
            l_mouse_pressed_  = true;
            l_mouse_realased_ = false;
        }

        if (l_mouse_pressed_ && l_mouse_realased_)
        {
            if (value_ > min_) value_--;
            l_mouse_pressed_  = false;
            l_mouse_realased_ = false;
        }
    }

    if (!r_mouse_inside_)
        r_mouse_realased_ = r_mouse_pressed_ = false;

    else
    {
        if (!mouse.isPressed(1))
            r_mouse_realased_ = true;

        if (mouse.isPressed(1) && r_mouse_realased_)
        {
            r_mouse_pressed_  = true;
            r_mouse_realased_ = false;
        }

        if (r_mouse_pressed_ && r_mouse_realased_)
        {
            value_++;
            r_mouse_pressed_  = false;
            r_mouse_realased_ = false;
        }
    }

    if (last_mouse_z_ && mouse.insideBox(x_+labelw+10, y_-5, x_+labelw+lw+w+80, y_+30) && last_mouse_z_ != mouse.getZ())
    {
        value_ += (mouse.getZ() - last_mouse_z_)*2;
    }

    if (value_ > max_) value_ = max_;
    if (value_ < min_) value_ = min_;

    last_mouse_z_ = mouse.getZ();
}

void selector_numeric::draw() const
{
    double labelw = al_get_text_width(font_, label_.c_str());
    double w = al_get_text_width(font_, std::to_string(int(value_)).c_str());
    double lw = al_get_bitmap_width(arrow_image);

    al_draw_bitmap(arrow_image, x_+labelw+20, y_+4, 0);
    al_draw_bitmap(arrow_image, x_+labelw+lw+w+60, y_+4, ALLEGRO_FLIP_HORIZONTAL);

    al_draw_text(font_, GRAY, x_, y_,ALLEGRO_ALIGN_LEFT, label_.c_str());
    al_draw_text(font_, GRAY, x_+labelw+lw+40+w/2, y_,ALLEGRO_ALIGN_CENTER, std::to_string(int(value_)).c_str());
}

bool selector_numeric::mouseOverArrow() const
{
    return r_mouse_inside_ || l_mouse_inside_;
}

void selector_numeric::setLabel(const std::string &label)
{
    label_ = label;
}

int selector_numeric::getValue() const
{
    return value_;
}
