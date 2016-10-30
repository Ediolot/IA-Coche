
#include "../include/button.hpp"


button::button(const std::string &text, ALLEGRO_BITMAP *img, ALLEGRO_COLOR color, ALLEGRO_FONT *font, const double animation_time):
    label(text, img, color, font),
    animation_time_(animation_time),
    line_size_(0),
    last_time_called_(0)
{}

button::button(ALLEGRO_BITMAP *img, const double animation_time):
    button("", img, al_map_rgb(0,0,0), nullptr, animation_time)
{}

button::button(const std::string &text, ALLEGRO_COLOR color, ALLEGRO_FONT *font, const double animation_time):
    button(text, nullptr, color, font, animation_time)
{}

button::~button()
{}

void button::update()
{
    label::update();
    if (mouse_over_)
        mouse.setShouldBeHand();
}

void button::draw()
{
    label::draw();

    if (animation_time_==0) return;

    // ANIMATION
    double current_time = al_get_time();
    double elapsed = current_time - last_time_called_;
    double label_w = text_w_ + img_w_;
    double label_h = text_h_ < img_h_ ? img_h_ : text_h_;

    if (last_time_called_>0)
    {
        if ( mouse_over_ && line_size_ < label_w) line_size_ += elapsed * label_w / animation_time_;
        if (!mouse_over_ && line_size_ >       0) line_size_ -= elapsed * label_w / animation_time_;

        if (line_size_ > 0)
            al_draw_line(img_x_+label_w/2-line_size_/2, y_+label_h+20, img_x_+label_w/2+line_size_/2, y_+label_h+20, color_, 2);
    }
    last_time_called_ = current_time;
}
