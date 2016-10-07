#ifndef MAP_HPP
#define MAP_HPP

#include <allegro5/allegro_primitives.h>
#include "common.hpp"

class map {
    private:
        double vertex[8];
    public:
        map(){};
        virtual ~map(){};

        void draw() const;
};

#endif
