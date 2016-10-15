#include "../include/button.hpp"


button::button(const std::string &label, const double animation_time):
    label_(label),
    x_(0),
    y_(0),
    w_(0),
    h_(0),
    min_w_(0),
    min_h_(0),
    mouse_inside_(false),
    mouse_pressed_(false),
    was_pressed_events_(0),
    animation_time_(animation_time),
    line_size_(0),
    last_time_called_(0)
{
    min_w_ = al_get_text_width(ubuntu_mono_font_40, label_.c_str())+2;
    min_h_ = al_get_font_line_height(ubuntu_mono_font_40)+2;
}

button::~button()
{}

void button::moveTo(const double x, const double y, const double w, const double h)
{
    x_ = x;
    y_ = y;
    w_ = w;
    h_ = h;
    if (w_ < min_w_) w_ = min_w_;
    if (h_ < min_h_) h_ = min_h_;
}

void button::update()
{
    mouse_inside_ = mouse.insideBox(x_, y_, x_+w_, y_+h_);

    if (!mouse_inside)
    {
        mouse_realased_ = false;
        mouse_presssed_ = false;
    }
    else
    {
        if (!mouse.isPressed(1))
            mouse_realased_ = true;

        if (mouse.isPressed(1) && mouse_realased_)
        {
            mouse_pressed_ = true;
            mouse_realased_ = false;
        }

        if (mouse_pressed_ && mouse_realased_)
        {
            was_pressed_events_++;
            mouse_pressed_ = false;
            mouse_realased_ = false;
        }
    }
}

void button::draw()
{
    // ANIMATION
    double current_time = al_get_time();
    double elapsed = current_time - last_time_called_;

    if (last_time_called_>0)
    {
        if ( mouse_inside_ && line_size_ < min_w_) line_size_ += elapsed * min_w_ / animation_time_;
        if (!mouse_inside_ && line_size_ >      0) line_size_ -= elapsed * min_w_ / animation_time_;

        if (line_size_ > 0)
            al_draw_line(x_+(w_-line_size_)/2, y_+h_/2+20, x_+(w_+line_size_)/2, y_+h_/2+20, GRAY, 2);
    }
    last_time_called_ = current_time;

    // TEXT
    al_draw_text(ubuntu_mono_font_40, GRAY, x_+w_/2, y_+(h_-min_h_)/2,ALLEGRO_ALIGN_CENTER, label_.c_str());
}

bool button::mouseOver() const
{
    return mouse_inside_;
}

void button::setLabel(const std::string &label)
{
    label_ = label;
    min_w_ = al_get_text_width(ubuntu_mono_font_40, label_.c_str())+2;
    if (w_ < min_w_) w_ = min_w_;
}

bool button::wasPressed()
{
    if (was_pressed_events_)
    {
        was_pressed_events_--;
        return true;
    }

    return false;
}
