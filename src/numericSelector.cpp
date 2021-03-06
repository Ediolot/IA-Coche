
#include "../include/numericSelector.hpp"

numericSelector::numericSelector(const std::string &text, ALLEGRO_BITMAP *img, ALLEGRO_FONT *font, ALLEGRO_COLOR color, int min, int max, int val):
    label_(text, img, color, font),
    show_(true),
    x_(.0),
    y_(.0),
    w_(.0),
    h_(.0),
    selector_x_(.0),
    selector_text_y_(.0),
    selector_img_y_(.0),
    text_h_(.0),
    img_w_(.0),
    img_h_(.0),
    max_(max),
    min_(min),
    value_(val),
    v_aling_(dir::CENTER),
    h_aling_(dir::CENTER),
    press_state_l_(0),
    press_state_r_(0),
    mouse_over_(false),
    last_mouse_z_(.0)
{
    text_h_ = al_get_font_line_height(font);
    img_w_ = al_get_bitmap_width(arrow_image);
    img_h_ = al_get_bitmap_height(arrow_image);
    setFont(font);
    setColor(color);
}

numericSelector::numericSelector(ALLEGRO_BITMAP *img, int min, int max, int val):
    numericSelector("", img, nullptr,  al_map_rgb(0,0,0), min, max, val)
{}

numericSelector::numericSelector(const std::string &text, ALLEGRO_FONT *font, ALLEGRO_COLOR color, int min, int max, int val):
    numericSelector(text, nullptr, font, color, min, max, val)
{}

numericSelector::~numericSelector()
{}

void numericSelector::resize(const double x, const double y, const double w, const double h)
{
    double label_w = label_.getMinWidth();
    double min_w   = getMinWidth();
    double min_h   = getMinHeight();

    x_ = x;
    y_ = y;
    w_ = w < min_w ? min_w : w;
    h_ = h < min_h ? min_h : h;

    switch (h_aling_)
    {
        case dir::LEFT:  selector_x_ = label_w;                break;
        case dir::RIGHT: selector_x_ = w_ - min_w + label_w;   break;
        default:         selector_x_ = (w_-min_w)/2 + label_w; break;
    }
    switch (v_aling_)
    {
        case dir::UP:   selector_img_y_ =    (min_h-img_h_)/2; selector_text_y_ =    (min_h-text_h_)/2; break;
        case dir::DOWN: selector_img_y_ = h_-(min_h-img_h_)/2; selector_text_y_ = h_-(min_h-text_h_)/2; break;
        default:        selector_img_y_ =    (h_   -img_h_)/2; selector_text_y_ =    (h_   -text_h_)/2; break;
    }

    selector_x_      += x;
    selector_img_y_  += y;
    selector_text_y_ += y;

    label_.resize(x_,y_);
}

void numericSelector::update()
{
    if (!show_)
    {
        mouse_over_ = false;
        press_state_l_ = 0;
        press_state_r_ = 0;
        last_mouse_z_ = mouse.getZ();
        return;
    }

    double arrow_l_x = selector_x_;
    double arrow_r_x = selector_x_+getMinWidth() - (img_w_+arrows_margin) - label_.getMinWidth();

    bool mouse_over_l = mouse.insideBox(arrow_l_x, y_, arrow_l_x+img_w_+arrows_margin, y_+img_h_);
    bool mouse_over_r = mouse.insideBox(arrow_r_x, y_, arrow_r_x+img_w_+arrows_margin, y_+img_h_);

    mouse_over_ = mouse.insideBox(x_, y_, x_+w_, y_+h_);

    if (mouse_over_r || mouse_over_l)
        mouse.setShouldBeHand();

    // Left arrow
    if (!mouse_over_l)
        press_state_l_ = 0;

    else
    {
        if (press_state_l_==0 && !mouse.leftDown())
            press_state_l_++;
        if (press_state_l_==1 &&  mouse.leftDown())
            press_state_l_++;
        if (press_state_l_==2 && !mouse.leftDown())
        {
            press_state_l_=0;
            value_--;
        }
    }

    // Right arrow
    if (!mouse_over_r)
        press_state_r_ = 0;

    else
    {
        if (press_state_r_==0 && !mouse.leftDown())
            press_state_r_++;
        if (press_state_r_==1 &&  mouse.leftDown())
            press_state_r_++;
        if (press_state_r_==2 && !mouse.leftDown())
        {
            press_state_r_=0;
            value_++;
        }
    }

    // Mouse zoom
    if (last_mouse_z_ && mouse.insideBox(arrow_l_x, y_, arrow_r_x+(img_w_+arrows_margin), y_+30))
        value_ += (mouse.getZ() - last_mouse_z_)*3;

    if (value_ >= max_) value_ = min_;
    if (value_ <  min_) value_ = max_-1;

    last_mouse_z_ = mouse.getZ();
}

void numericSelector::draw()
{
    if (!show_) return;

    double text_w = al_get_text_width(font_, std::to_string(value_).c_str());

    label_.draw();
    al_draw_bitmap(arrow_image, selector_x_+arrows_margin/2, selector_img_y_, 0);
    al_draw_bitmap(arrow_image, selector_x_+img_w_+text_w+arrows_margin*3/2, selector_img_y_, ALLEGRO_FLIP_HORIZONTAL);

    if (font_)
        al_draw_text(font_, color_, selector_x_+img_w_+arrows_margin, y_,ALLEGRO_ALIGN_LEFT, std::to_string(value_).c_str());
}

int numericSelector::getValue() const
{
    return value_;
}

bool numericSelector::mouseOver()
{
    return mouse_over_;
}

void numericSelector::setText(const std::string &text)
{
    label_.setText(text);
    resize(x_, y_, w_, h_);
}

void numericSelector::setImg(ALLEGRO_BITMAP *img)
{
    label_.setImg(img);
    resize(x_, y_, w_, h_);
}

void numericSelector::setFont(ALLEGRO_FONT *font)
{
    font_ = font;
    label_.setFont(font);
    resize(x_, y_, w_, h_);
}

void numericSelector::setColor(ALLEGRO_COLOR color)
{
    color_ = color;
    label_.setColor(color);
}

void numericSelector::setVerticalTextAling(const dir v_aling)
{
    v_aling_ = v_aling;
    label_.setVerticalTextAling(v_aling);
    resize(x_, y_, w_, h_);
}

void numericSelector::setHorizontalTextAling(const dir h_aling)
{
    h_aling_ = h_aling;
    label_.setHorizontalTextAling(h_aling);
    resize(x_, y_, w_, h_);
}

double numericSelector::getMinWidth() const
{
    return label_.getMinWidth() + img_w_*2 + al_get_text_width(font_, std::to_string(value_).c_str()) + arrows_margin*2;
}

double numericSelector::getMinHeight() const
{
    return label_.getMinHeight() > img_h_ ? label_.getMinHeight() : img_h_;
}

void numericSelector::show(bool show)
{
    show_ = show;
}

void numericSelector::hide()
{
    show_ = false;
}
