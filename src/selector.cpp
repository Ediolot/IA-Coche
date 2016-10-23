#include "../include/selector.hpp"

selector::selector(const std::vector<std::string>& list, const std::string &text, ALLEGRO_BITMAP *img, ALLEGRO_FONT *font, ALLEGRO_COLOR *color):
    label(text, img, font, color),
    list_(list),
    selected_(0),
    biggest_item_w_(.0),
    r_mouse_inside_(false),
    r_mouse_pressed_(false),
    r_mouse_realased_(false),
    l_mouse_inside_(false),
    l_mouse_pressed_(false),
    l_mouse_realased_(false)
{
    uint index = 0;
    for (uint i=0; i<list.size(); ++i)
        if (list[i].size() > list[index].size())
            index = i;

    biggest_item_w_ = al_get_text_width(font_, list[index].c_str());
}

selector::selector(const std::vector<std::string>& list, ALLEGRO_BITMAP *img, ALLEGRO_FONT *font, ALLEGRO_COLOR *color):
    selector(list, "", img, font, color)
{}

selector::selector(const std::vector<std::string>& list, const std::string &text, ALLEGRO_FONT *font, ALLEGRO_COLOR *color):
    selector(list, text, nullptr, font, color)
{}

selector::~selector()
{}

void selector::resize(const double x, const double y, const double w, const double h)
{
    label::resize();
}

void selector::update()
{
    double labelw = al_get_text_width(font_, label_.c_str());
    double lw = al_get_bitmap_width(arrow_image);

    l_mouse_inside_ = mouse.insideBox(x_+labelw+10, y_-5, x_+labelw+lw+40, y_+30);
    r_mouse_inside_ = mouse.insideBox(x_+labelw+lw+w_+50, y_-5, x_+labelw+lw+w_+80, y_+30);

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
            selected_ = selected_==0 ? list_.size()-1 : selected_-1;
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
            selected_ = selected_==(list_.size()-1) ? 0 : selected_+1;
            r_mouse_pressed_  = false;
            r_mouse_realased_ = false;
        }
    }
}

void selector::draw() const
{
    double labelw = al_get_text_width(font_, label_.c_str());
    double lw = al_get_bitmap_width(arrow_image);

    al_draw_bitmap(arrow_image, x_+labelw+20, y_+4, 0);
    al_draw_bitmap(arrow_image, x_+labelw+lw+w_+60, y_+4, ALLEGRO_FLIP_HORIZONTAL);

    al_draw_text(font_, GRAY, x_, y_,ALLEGRO_ALIGN_LEFT, label_.c_str());
    al_draw_text(font_, GRAY, x_+labelw+lw+40+w_/2, y_,ALLEGRO_ALIGN_CENTER, list_[selected_].c_str());
}

bool selector::mouseOverArrow() const
{
    return r_mouse_inside_ || l_mouse_inside_;
}

void selector::setLabel(const std::string &label)
{
    label_ = label;
}

uint selector::getSelectedIndex() const
{
    return selected_;
}
