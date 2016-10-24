#include "../include/label.hpp"


label::label(const std::string &text, ALLEGRO_BITMAP *img, ALLEGRO_FONT *font, ALLEGRO_COLOR *color):
    color_(nullptr),
    font_(nullptr),
    img_(nullptr),
    text_(text),
    x_(.0),
    y_(.0),
    w_(.0),
    h_(.0),
    text_x_(.0),
    text_y_(.0),
    img_x_(.0),
    img_y_(.0),
    text_w_(.0),
    text_h_(.0),
    img_w_(.0),
    img_h_(.0),
    v_aling_(dir::CENTER),
    h_aling_(dir::CENTER),
    mouse_over_(false),
    press_state_(0U),
    onclick_(nullptr),
    onmouseover_(nullptr)
{
    setText(text);
    setFont(font);
    setColor(color);
    setImg(img);
}

label::label(ALLEGRO_BITMAP *img, ALLEGRO_FONT *font, ALLEGRO_COLOR *color):
    label("", img, font, color)
{}

label::label(const std::string &text, ALLEGRO_FONT *font, ALLEGRO_COLOR *color):
    label(text, nullptr, font, color)
{}

label::~label()
{}

void label::resize(const double x, const double y, const double w, const double h)
{
    double min_w = getMinWidth();
    double min_h = getMinHeight();

    x_ = x;
    y_ = y;
    w_ = w < min_w ? min_w : w;
    h_ = h < min_h ? min_h : h;

    switch (h_aling_)
    {
        case dir::LEFT:  img_x_ = 0;                     break;
        case dir::RIGHT: img_x_ = w_ - min_w;            break;
        default:         img_x_ = (w_-text_w_+img_w_)/2; break;
    }
    switch (v_aling_)
    {
        case dir::UP:   img_y_ =    (min_h-img_h_)/2; text_y_ =    (min_h-text_h_)/2; break;
        case dir::DOWN: img_y_ = h_-(min_h-img_h_)/2; text_y_ = h_-(min_h-text_h_)/2; break;
        default:        img_y_ =    (h_   -img_h_)/2; text_y_ =    (h_-   text_h_)/2; break;
    }

    text_x_ = img_x_ + img_w_;
}

void label::update()
{
    bool mouse_over = mouse.insideBox(x_, y_, x_+w_, y_+h_);

    if (mouse_over && !mouse_over_ && onmouseover_)
        onmouseover_();

    mouse_over_ = mouse_over;


    if (!mouse_over_)
        press_state_ = 0;

    else
    {
        if (press_state_==0 && !mouse.leftPressed())
            press_state_++;
        if (press_state_==1 &&  mouse.leftPressed())
            press_state_++;
        if (press_state_==2 && !mouse.leftPressed())
        {
            press_state_=0;
            if (onclick_) onclick_();
        }
    }
}

void label::draw()
{
    if (img_)
        al_draw_bitmap(img_, img_x_, img_y_, 0);
    if (font_ && color_)
        al_draw_text(font_, *color_, text_x_, text_y_, ALLEGRO_ALIGN_CENTER, text_.c_str());
}

void label::onMouseClick(void (*f)())
{
    onclick_ = f;
}

void label::onMouseOver(void (*f)())
{
    onmouseover_ = f;
}

bool label::mouseOver()
{
    return mouse_over_;
}

void label::setText(const std::string &text)
{
    text_ = text;
    text_w_ = al_get_text_width(font_, text_.c_str());
    text_h_ = al_get_font_line_height(font_);
    resize(x_, y_, w_, h_);
}

void label::setImg(ALLEGRO_BITMAP *img)
{
    img_ = img;
    img_w_ = img ? al_get_bitmap_width(img_) : 0;
    img_h_ = img ? al_get_bitmap_height(img_) : 0;
    resize(x_, y_, w_, h_);
}

void label::setFont(ALLEGRO_FONT *font)
{
    font_ = font;
    text_w_ = font ? al_get_text_width(font_, text_.c_str()) : 0;
    text_h_ = font ? al_get_font_line_height(font_) : 0;
    resize(x_, y_, w_, h_);
}

void label::setColor(ALLEGRO_COLOR *color)
{
    color_ = color;
}

void label::setVerticalTextAling(const dir v_aling)
{
    v_aling_ = v_aling;
    resize(x_, y_, w_, h_);
}

void label::setHorizontalTextAling(const dir h_aling)
{
    h_aling_ = h_aling;
    resize(x_, y_, w_, h_);
}

double label::getMinWidth() const
{
    return text_w_ + img_w_;
}

double label::getMinHeight() const
{
    return text_h_ > img_h_ ? text_h_ : img_h_;
}
