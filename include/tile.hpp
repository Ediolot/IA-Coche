/*
    REPRESENTS A TILE
*/

#ifndef TILE_HPP
#define TILE_HPP

#include <allegro5/allegro_primitives.h>
#include <vector>
#include "fonts.hpp"
#include "common.hpp"

class tile {

    private:

        std::vector<tile*> neighbors_;
        std::vector<tile*> adjacents_;
        std::vector<point> vertices_;

        ALLEGRO_COLOR color_;
        bool is_border_;

    public:

        // Constructs a tile with those vertices
        tile(const std::vector<point>& v, const bool is_border);
        virtual ~tile();

        void storeFriend(tile *n, const dir direction);
        tile* getFriend(const dir direction) const;
        bool isAdjacentTo(const tile *n) const;

        // Check if is a border tile
        bool isBorder() const;

        // Draw the tile
        void draw() const;

        // Change the tile color
        void setColor(ALLEGRO_COLOR color);
};

#endif
