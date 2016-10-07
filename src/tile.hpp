/*
    REPRESENTS A TILE
*/

#ifndef TILE_HPP
#define TILE_HPP

#include <allegro5/allegro_primitives.h>
#include "common.hpp"

class tile {

    private:

        point vertices_[4]; // Vertices of the tile

    public:

        // Constructs a tile with those vertices
        tile(const point v[4]);
        virtual ~tile();

        // Draw the tile
        void draw() const;
};

#endif
