/*
    REPRESENTS THE TILES MAP

    Container with multiple tiles elements.
*/

#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include "common.hpp"
#include "tile.hpp"

class map {

    const double BORDER = 0.1; // Separation between tiles

    private:

        std::vector<tile> tiles_; // Tiles
        point vertices_[4];       // Container vertices
        uint size_;               // Number of tiles in a side

    public:

        // Creates the map centered with the max width or height available inside a square
        map(const uint size, const double screenWidth, const double screenHeight, const double percent = 0.9);
        virtual ~map();

        // Draw all the tiles
        void draw() const;
};

#endif
