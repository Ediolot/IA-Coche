/*
    REPRESENTS A TILE
*/

#ifndef TILE_HPP
#define TILE_HPP

#include <allegro5/allegro_primitives.h>
#include <vector>
#include "common.hpp"

class tile {

    private:

        //std::vector<tile*> neighbors_;
        point vertices_[4]; // Vertices of the tile
        ALLEGRO_COLOR color_;
        bool is_border_;

    public:

        // Constructs a tile with those vertices
        tile(const point v[4], const bool is_border);
        virtual ~tile();

        // Check if is a border tile
        bool isBorder() const;

        // Draw the tile
        void draw() const;

        // Change the tile color
        void setColor(ALLEGRO_COLOR color);
};

#endif
