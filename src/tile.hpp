#ifndef TILE_HPP
#define TILE_HPP

#include <allegro5/allegro_primitives.h>
#include "common.hpp"

class tile {

    private:

        point vertices_[4];

    public:

        tile(const point v[4]);
        virtual ~tile();

        void draw() const;
};

#endif
