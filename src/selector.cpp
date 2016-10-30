#include "../include/selector.hpp"

selector::selector(const std::vector<std::string>& list, const std::string &text, ALLEGRO_BITMAP *img, ALLEGRO_FONT *font, ALLEGRO_COLOR color):
    numericSelector(text, img, font, color, 0, list.size()),
    list_(list),
    biggest_item_w_(.0)
{
    if (list.size())
    {
        uint index = 0;
        for (uint i=0; i<list.size(); ++i)
            if (list[i].size() > list[index].size())
                index = i;

        biggest_item_w_ = al_get_text_width(font_, list[index].c_str());
    }
}

selector::selector(const std::vector<std::string>& list, ALLEGRO_BITMAP *img):
    selector(list, "", img, nullptr, al_map_rgb(0,0,0))
{}

selector::selector(const std::vector<std::string>& list, const std::string &text, ALLEGRO_FONT *font, ALLEGRO_COLOR color):
    selector(list, text, nullptr, font, color)
{}

selector::~selector()
{}

void selector::draw()
{
    if (!show_) return;
    
    double text_w = font_ ? al_get_text_width(font_, list_[value_].c_str()) : 0;

    label_.draw();
    al_draw_bitmap(arrow_image, selector_x_+arrows_margin/2, selector_img_y_, 0);
    al_draw_bitmap(arrow_image, selector_x_+img_w_+text_w+arrows_margin*3/2, selector_img_y_, ALLEGRO_FLIP_HORIZONTAL);

    if (font_)
        al_draw_text(font_, color_, selector_x_+img_w_+arrows_margin, y_,ALLEGRO_ALIGN_LEFT, list_[value_].c_str());
}

double selector::getMinWidth() const
{
    return label_.getMinWidth() + img_w_*2 + biggest_item_w_ + arrows_margin*2;
}
