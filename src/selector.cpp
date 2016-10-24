#include "../include/selector.hpp"

selector::selector(const std::vector<std::string>& list, const std::string &text, ALLEGRO_BITMAP *img, ALLEGRO_FONT *font, ALLEGRO_COLOR *color):
    numericSelector(text, img, font, color, 0, list.size()),
    list_(list),
    biggest_item_w_(.0)
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

void selector::draw()
{
    double text_w = al_get_text_width(font_, list_[value_].c_str());

    label_.draw();
    al_draw_bitmap(arrow_image, selector_x_+5, selector_img_y_, 0);
    al_draw_bitmap(arrow_image, selector_x_+img_w_+15+text_w, selector_img_y_, 0);

    if (font_ && color_)
        al_draw_text(font_, *color_, selector_x_+text_w/2+img_w_+10, y_,ALLEGRO_ALIGN_CENTER, list_[value_].c_str());
}

double selector::getMinWidth() const
{
    return label_.getMinWidth() + img_w_*2 + biggest_item_w_;
}
