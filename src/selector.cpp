#include "../include/selector.hpp"

selector::selector(const std::string &label, const std::vector<std::string>& list, const std::string& arrow_path):
    label_(label),
    list_(list),
    selected_(0),
    arrow_(nullptr),
    x_(0),
    y_(0),
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

    w_ = al_get_text_width(ubuntu_mono_font_40, list[index].c_str());

    arrow_  = al_load_bitmap(arrow_path.c_str());
}

selector::~selector()
{
    al_destroy_bitmap(arrow_);
}

void selector::moveTo(const double x, const double y)
{
    x_ = x;
    y_ = y;
}

void selector::update()
{
    double labelw = al_get_text_width(ubuntu_mono_font_40, label_.c_str());
    double lw = arrow_ ? al_get_bitmap_width(arrow_) : 0;

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

void selector::draw()
{
    double labelw = al_get_text_width(ubuntu_mono_font_40, label_.c_str());
    double lw = arrow_ ? al_get_bitmap_width(arrow_) : 0;

    if (arrow_) al_draw_bitmap(arrow_, x_+labelw+20, y_+4, 0);
    if (arrow_) al_draw_bitmap(arrow_, x_+labelw+lw+w_+60, y_+4, ALLEGRO_FLIP_HORIZONTAL);

    al_draw_text(ubuntu_mono_font_40, GRAY, x_, y_,ALLEGRO_ALIGN_LEFT, label_.c_str());
    al_draw_text(ubuntu_mono_font_40, GRAY, x_+labelw+lw+40+w_/2, y_,ALLEGRO_ALIGN_CENTER, list_[selected_].c_str());
}

bool selector::mouseOverArrow() const
{
    return r_mouse_inside_ || l_mouse_inside_;
}

void selector::setLabel(const std::string &label)
{
    label_ = label;
}

uint selector::getSelectedIndex()
{
    return selected_;
}
