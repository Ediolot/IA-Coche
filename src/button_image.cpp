#include "../include/button_image.hpp"


button_image::button_image(const std::string &path):
    path_(path),
    image_(nullptr),
    x_(0),
    y_(0),
    w_(0),
    h_(0),
    min_w_(0),
    min_h_(0),
    mouse_inside_(false),
    mouse_pressed_(false),
    mouse_realased_(false),
    was_pressed_events_(0)
{
    image_ = al_load_bitmap(path.c_str());
    if (image_)
    {
        min_w_ = al_get_bitmap_width(image_)+2;
        min_h_ = al_get_bitmap_height(image_)+2;
    }
}

button_image::~button_image()
{
    al_destroy_bitmap(image_);
}

void button_image::moveTo(const double x, const double y, const double w, const double h)
{
    x_ = x;
    y_ = y;
    w_ = w;
    h_ = h;
    if (w_ < min_w_) w_ = min_w_;
    if (h_ < min_h_) h_ = min_h_;
}

void button_image::update()
{
    mouse_inside_ = mouse.insideBox(x_, y_, x_+w_, y_+h_);

    if (!mouse_inside_)
    {
        mouse_realased_ = false;
        mouse_pressed_ = false;
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

void button_image::draw()
{
    if (image_) al_draw_bitmap(image_, x_+(w_-min_w_)/2, y_+(h_-min_h_)/2, 0);
}

bool button_image::mouseOver() const
{
    return mouse_inside_;
}

void button_image::setImage(const std::string &path)
{
    if (path == path_) return;

    path_ = path;
    al_destroy_bitmap(image_);
    image_ = al_load_bitmap(path.c_str());

    if (!image_) return;

    if (w_ < min_w_) w_ = min_w_;
    if (h_ < min_h_) h_ = min_h_;
}

bool button_image::wasPressed()
{
    if (was_pressed_events_)
    {
        was_pressed_events_--;
        return true;
    }

    return false;
}
