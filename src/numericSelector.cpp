#include "../include/numericSelector.hpp"

numericSelector(const std::string &text, ALLEGRO_BITMAP *img, ALLEGRO_FONT *font, ALLEGRO_COLOR *color, int min, int max, int val):
    color_(nullptr),
    font_(nullptr),
    label_(text, img, font_, color_),
    x_(.0),
    y_(.0),
    w_(.0),
    h_(.0),
    selector_x_(.0),
    selector_text_y_(.0),
    selector_img_y_(.0),
    text_h_(.0),
    img_h_(.0),
    img_w_(.0),
    max_(max),
    min_(min),
    value_(val),
    v_aling_(vAling::CENTER),
    h_aling_(hAling::CENTER),
    press_state_left_(0),
    press_state_right_(0),
    mouse_over_(false),
    onmouseover_(nullptr),
    last_mouse_z_(.0)
{
    text_h_ = al_get_font_line_height(font_);
    img_x_ = al_get_bitmap_width(arrow_image);
    img_h_ = al_get_bitmap_height(arrow_image);
    setFont(font);
    setColor(color);
}

numericSelector(ALLEGRO_BITMAP *img, ALLEGRO_FONT *font, ALLEGRO_COLOR *color, int min, int max, int val):
    numericSelector("", img, font, color, min, max, val)
{}

numericSelector(const std::string &text, ALLEGRO_FONT *font, ALLEGRO_COLOR *color, int min, int max, int val):
    numericSelector(text, nullptr, font, color, min, max, val)
{}

numericSelector::~numericSelector()
{}

void selector_numeric::resize(const double x, const double y, const double w, const double h)
{
    double min_w   = getMinWidth();
    double min_h   = getMinHeight();

    min_w += 10; // Label <=> selector margin
    min_w += 20; // Arrows margin

    x_ = x;
    y_ = y;
    w_ = w < min_w ? min_w : w;
    h_ = h < min_h ? min_h : h;

    switch (h_aling_)
    {
        case hAling::LEFT:  selector_x_ = label_w;                break;
        case hAling::RIGHT: selector_x_ = w_ - min_w + label_w;   break;
        default:            selector_x_ = (w_-min_w)/2 + label_w; break;
    }
    switch (v_aling_)
    {
        case vAling::TOP:    selector_img_y_ =    (min_h-img_h_)/2; selector_text_y_ =    (min_h-text_h_)/2; break;
        case vAling::BOTTOM: selector_img_y_ = h_-(min_h-img_h_)/2; selector_text_y_ = h_-(min_h-text_h_)/2; break;
        default:             selector_img_y_ =    (h_   -img_h_)/2; selector_text_y_ =    (h_   -text_h_)/2; break;
    }

    label_.resize(x_,y_);
}

void selector_numeric::update()
{
    double arrow_l_x = selector_x_+label_.getMinWidth()+10;
    double arrow_r_x = selector_x_+getMinWidth() - (img_w+10);

    bool mouse_over_l = mouse.insideBox(arrow_l_x, y_, arrow_l_x+img_w_+10, y_+img_h_);
    bool mouse_over_r = mouse.insideBox(arrow_r_x, y_, arrow_r_x+img_w_+10, y_+img_h_);
    bool mouse_over   = mouse.insideBox(x_, y_, x_+w_, y_+h_);

    if (mouse_over && !mouse_over_ && onmouseover_)
        onmouseover_();

    mouse_over_ = mouse_over;

    if (mouse_over_r || mouse_over_l)
        mouse.setShouldBeHand();

    // Left arrow
    if (!mouse_over_l)
        press_state_l_ = 0;

    else
    {
        if (press_state_l_==0 && !mouse.leftPressed())
            press_state_l_++;
        if (press_state_l_==1 &&  mouse.leftPressed())
            press_state_l_++;
        if (press_state_l_==2 && !mouse.leftPressed())
        {
            press_state_l_=0;
            value--;
        }
    }

    // Right arrow
    if (!mouse_over_r)
        press_state_r_ = 0;

    else
    {
        if (press_state_r_==0 && !mouse.leftPressed())
            press_state_r_++;
        if (press_state_r_==1 &&  mouse.leftPressed())
            press_state_r_++;
        if (press_state_r_==2 && !mouse.leftPressed())
        {
            press_state_r_=0;
            value++;
        }
    }

    // Mouse zoom
    if (last_mouse_z_ && mouse.insideBox(arrow_l_x, y_, arrow_r_x+(img_w+10), y_+30))
        value_ += (mouse.getZ() - last_mouse_z_)*3;

    if (value_ > max_) value_ = min_;
    if (value_ < min_) value_ = max_;

    last_mouse_z_ = mouse.getZ();
}

void selector_numeric::draw()
{
    double text_w = al_get_text_width(font_, std::to_string(value_).c_string());

    label_.draw();
    al_draw_bitmap(arrow_image, selector_x_+5, selector_img_y_);
    al_draw_bitmap(arrow_image, selector_x_+img_w_+15+text_w, selector_img_y_);

    if (font_ && color_)
        al_draw_text(font_, color_, selector_x_+text_w/2+img_w_+10, y_,ALLEGRO_ALIGN_CENTER, std::to_string(value_).c_str());
}

int selector_numeric::getValue() const
{
    return value_;
}

void label::onMouseOver(const std::function<void()> &f)
{
    onmouseover_ = f;
}

bool label::mouseOver()
{
    return mouse_over_;
}

void label::setText(const std::string &text)
{
    label_.setText(text);
    resize(x_, y_, w_, h_)
}

void label::setImg(ALLEGRO_BITMAP *img)
{
    label_.setImg(img);
    resize(x_, y_, w_, h_);
}

void label::setFont(ALLEGRO_FONT *font)
{
    font_ = font;
    label_.setFont(font);
    resize(x_, y_, w_, h_);
}

void label::setColor(ALLEGRO_COLOR *color)
{
    color_ = color;
    label_.setColor(color);
}

void setVerticalTextAling(const vAling v_aling)
{
    v_aling_ = v_aling;
    label.setVerticalTextAling(v_aling);
    resize(x_, y_, w_, h_);
}

void setHorizontalTextAling(const hAling h_aling)
{
    h_aling_ = h_aling;
    label.setHorizontalTextAling(h_aling);
    resize(x_, y_, w_, h_);
}

double getMinWidth() const
{
    return label_.getMinWidth() + img_w_*2 + al_get_text_width(font_, std::to_string(value_).c_string());
}

double getMinHeight() const
{
    return label_.getMinHeight() > img_h_ ? label_.getMinHeight() : img_h_;
}