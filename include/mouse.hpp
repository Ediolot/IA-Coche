#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <allegro5/allegro.h>

class _mouse {

    private:

        bool should_be_hand_;
        bool inside_screen_;
        bool button_1_;
        bool button_2_;
        bool button_3_;
        double x_;
        double y_;
        double z_;

        ALLEGRO_SYSTEM_MOUSE_CURSOR cursor_;

    public:

        _mouse();
        virtual ~_mouse();

        double getX() const;

        double getY() const;

        double getZ() const;

        void updatePos(const ALLEGRO_EVENT &ev);

        void intoScreen();

        void outoScreen();

        void press(const ALLEGRO_EVENT &ev);

        void realase(const ALLEGRO_EVENT &ev);

        bool isPressed(uint button) const;

        bool leftPressed() const;
        bool rightPressed() const;
        bool centerPressed() const;

        bool insideBox(const double x1, const double y1, const double x2, const double y2) const;

        void setCursor(const ALLEGRO_SYSTEM_MOUSE_CURSOR id);

        ALLEGRO_SYSTEM_MOUSE_CURSOR getCursor() const;

        void setShouldBeHand(bool val = true);
        bool shouldBeHand() const;
};

#endif
