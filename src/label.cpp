#include "../include/label.hpp"


label::label(const std::string &label, ALLEGRO_BITMAP *img, ALLEGRO_FONT *font, ALLEGRO_COLOR *color):
    color_(nullptr),
    font_(nullptr),
    img_(nullptr),
    label_(label),
    x_(.0),
    y_(.0),
    w_(.0),
    h_(.0),
    mouse_over_(false),
    press_state_(0U),
    label_w_(.0),
    label_h_(.0),
    img_w_(.0),
    img_h_(.0),
    v_aling_(vAling::CENTER),
    h_aling_(hAling::CENTER),
    onclick_(nullptr),
    onmouseover_(nullptr)
{
    setLabel(label);
    setFont(font);
    setColor(color);
    setImg(img);
}

label::label(ALLEGRO_BITMAP *img, ALLEGRO_FONT *font, ALLEGRO_COLOR *color):
    label("", img, font, color)
{}

label::label(const std::string &label, ALLEGRO_FONT *font, ALLEGRO_COLOR *color):
    label(label, nullptr, font, color)
{}

label::~label()
{}

void label::resize(const double x, const double y, const double w, const double h)
{
    double min_w = label_w_+img_w_;
    double min_h = label_h_+img_h_;

    x_ = x;
    y_ = y;
    w_ = w < min_w ? min_w : w;
    h_ = h < min_h ? min_h : h;
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
    double label_x, label_y;
    double img_x, img_y;

    switch (h_aling_)
    {
        case hAling::LEFT:  img_x = 0;                      break;
        case hAling::RIGHT: img_x = w_-label_w_-img_w_;     break;
        default:            img_x = (w_-label_w_+img_w_)/2; break;
    }
    switch (v_aling_)
    {
        case vAling::TOP:    img_y = label_y = 0;                              break;
        case vAling::BOTTOM: img_y = h_-img_h_;     label_y = h_-label_y_;     break;
        default:             img_y = (h_-img_h_)/2; label_y = (h_-label_h_)/2; break;
    }

    label_x = img_x + img_w_;

    if (img_)
        al_draw_bitmap(img_, img_x_, img_y_);
    if (font_ && color_)
        al_draw_text(font_, color_, label_x, label_y, ALLEGRO_ALIGN_CENTER, label_.c_str());
}

void label::onMouseClick(const std::function<void()> &f)
{
    onclick_ = f;
}

void label::onMouseOver(const std::function<void()> &f)
{
    onmouseover_ = f;
}

bool label::mouseOver()
{
    return mouse_over_;
}

void label::setLabel(const std::string &label)
{
    label_ = label;
    label_w_ = al_get_text_width(font_, label_.c_str());
    label_h_ = al_get_font_line_height(font_);
    resize(x_, y_, w_, h_);
}

void label::setImg(ALLEGRO_BITMAP *img)
{
    img_ = img;
    img_w_ = img ? al_get_bitmap_width(image_) : 0;
    img_h_ = img ? al_get_bitmap_height(image_) : 0;
    resize(x_, y_, w_, h_);
}

void label::setFont(ALLEGRO_FONT *font)
{
    font_ = font;
    label_w_ = font ? al_get_text_width(font_, label_.c_str()) : 0;
    label_h_ = font ? al_get_font_line_height(font_) : 0;
    resize(x_, y_, w_, h_);
}

void label::setColor(ALLEGRO_COLOR *color)
{
    color_ = color;
}
