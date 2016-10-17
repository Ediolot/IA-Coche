/*
    REPRESENTS A TILE
*/

#ifndef TILE_HPP
#define TILE_HPP

#include <allegro5/allegro_primitives.h>
#include <vector>
#include <cmath>
#include <utility>
#include "fonts.hpp"
#include "common.hpp"
#include "utility.hpp"

class tile {

    private:

        std::vector<tile*> neighbors_;
        std::vector<tile*> adjacents_;

        ALLEGRO_COLOR tile_color_;
        tileType tile_type_;

    public:

        tile();
        virtual ~tile();

        // Add a tile's friend
        void addFriend(tile *n, const dir direction);

        // Get a tile's friend
        tile* getFriend(const dir direction) const;

        // Tell's if a tile is adjacent to another
        bool isAdjacentTo(const tile *n) const;

        // Check if is a border tile
        bool isBorder() const;

        // Check if the tile's type is water
        bool isWater() const;

        // Append the tile's vertices points to a vector
        void appendVertices(
            std::vector<ALLEGRO_VERTEX> &floor,
            std::vector<ALLEGRO_VERTEX> &obs, 
            const double cx,
            const double cy,
            const double width,
            const double border,
            const double max_x,
            const double max_y
        ) const;

        // Change the tile color
        void setType(const tileType type);
};


#endif
