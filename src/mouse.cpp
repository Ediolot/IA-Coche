
#include "../include/mouse.hpp"

_mouse::_mouse():
    inside_screen_(true),
    button_1_(false),
    button_2_(false),
    button_3_(false),
    x_(0),
    y_(0),
    z_(0),
    cursor_(ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)
{
    auto display = al_get_current_display();
    if (display != nullptr)
        al_set_system_mouse_cursor(al_get_current_display(), cursor_);
}

_mouse::~_mouse()
{}

double _mouse::getX() const
{
    return x_;
}

double _mouse::getY() const
{
    return y_;
}

double _mouse::getZ() const
{
    return z_;
}

void _mouse::updatePos(const ALLEGRO_EVENT &ev)
{
    x_ = ev.mouse.x;
    y_ = ev.mouse.y;
    z_ = ev.mouse.z;
}

void _mouse::intoScreen()
{
    inside_screen_ = true;
}

void _mouse::outoScreen()
{
    inside_screen_ = false;
}

void _mouse::press(const ALLEGRO_EVENT &ev)
{
    if (ev.mouse.button == 1) button_1_ = true;
    if (ev.mouse.button == 2) button_2_ = true;
    if (ev.mouse.button == 3) button_3_ = true;
}

void _mouse::realase(const ALLEGRO_EVENT &ev)
{
    if (ev.mouse.button == 1) button_1_ = false;
    if (ev.mouse.button == 2) button_2_ = false;
    if (ev.mouse.button == 3) button_3_ = false;
}

bool _mouse::insideBox(const double x1, const double y1, const double x2, const double y2) const
{
    return x_ >= x1 && x_ <= x2 && y_ >= y1 && y_ <= y2;
}

void _mouse::setCursor(const ALLEGRO_SYSTEM_MOUSE_CURSOR id)
{
    if (cursor_ == id) return;

    cursor_ = id;
    auto display = al_get_current_display();
    if (display != nullptr)
        al_set_system_mouse_cursor(al_get_current_display(), cursor_);
}

ALLEGRO_SYSTEM_MOUSE_CURSOR _mouse::getCursor() const
{
    return cursor_;
}

bool _mouse::isPressed(uint button) const
{
    switch (button)
    {
        case 1: return button_1_;
        case 2: return button_2_;
        case 3: return button_3_;
        default: return false;
    }
}

bool _mouse::leftDown() const
{
    return button_1_;
}

bool _mouse::rightDown() const
{
    return button_2_;
}

bool _mouse::centerDown() const
{
    return button_3_;
}

void _mouse::setShouldBeHand(bool val)
{
    should_be_hand_ = val;
}

bool _mouse::shouldBeHand() const
{
    return should_be_hand_;
}
