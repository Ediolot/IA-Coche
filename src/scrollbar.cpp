
#include "../include/scrollbar.hpp"


scrollbar::scrollbar(const scrollbar::type type, const double value):
    show_(true),
    type_(type),
    value_(value),
    x_(0),
    y_(0),
    w_(0),
    h_(0),
    last_mouse_z_(0),
    mouse_inside_(false),
    scrolling_(false)
{}

scrollbar::~scrollbar()
{}

void scrollbar::resize(const double x, const double y, const double w, const double h)
{
    x_ = x;
    y_ = y;
    w_ = w;
    h_ = h;
}

void scrollbar::update()
{
    if (!show_)
    {
        mouse_inside_ = false;
        scrolling_ = false;
        last_mouse_z_ = mouse.getZ();
        return;
    }

    if (type_==VERTICAL)
        mouse_inside_ = mouse.insideBox(x_-20, y_, x_+w_+20, y_+h_);
    else
        mouse_inside_ = mouse.insideBox(x_, y_-20, x_+w_, y_+h_+20);

    if (mouse_inside_ && mouse.leftDown())
        scrolling_ = true;

    if (!mouse.isPressed(1))
        scrolling_ = false;

    if (scrolling_)
    {
        value_ = type_==VERTICAL ? (1.0 - (mouse.getY()-y_)/h_) : (mouse.getX()-x_)/w_;
        if (value_ > 1.0) value_ = 1.0;
        if (value_ < 0.0) value_ = 0.0;
    }
    else if (mouse_inside_ && last_mouse_z_ != mouse.getZ())
    {
        value_ += (mouse.getZ() - last_mouse_z_)*0.05;
        if (value_ > 1.0) value_ = 1.0;
        if (value_ < 0.0) value_ = 0.0;
    }

    last_mouse_z_ = mouse.getZ();
}

void scrollbar::draw()
{
    if (!show_) return;

    al_draw_filled_rectangle(x_, y_, x_+w_, y_+h_, LIGHT_GRAY);

    if (type_==VERTICAL)
        al_draw_filled_rectangle(x_+w_, y_+h_, x_, y_-(h_*value_)+h_, ORANGE_STRONG);
    else
        al_draw_filled_rectangle(x_, y_, x_+w_*value_, y_+h_, ORANGE_STRONG);
}

double scrollbar::getValue() const
{
    return value_;
}

void scrollbar::setValue(const double value)
{
    value_ = value;
}

void scrollbar::show(bool show)
{
    show_ = show;
}

void scrollbar::hide()
{
    show_ = false;
}
