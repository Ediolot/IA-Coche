/*
    REPRESENTS THE TILES MAP

    Container with multiple tiles elements.
*/

#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <ctime>
#include <random>
#include <iostream> // TODO Delete
#include <algorithm>
#include "common.hpp"
#include "utility.hpp"
#include "tile.hpp"

/* TILES:
              UP
   UP_LEFT    |     UP_RIGHT
           \  |   /
 LEFT ----- CENTER ----- RIGHT
           /  |   \
 DOWN_LEFT    |     DOWN_RIGHT
            DOWN
*/

class map {

    const double BORDER = 0.1; // Separation between tiles

    private:

        std::vector<tile> tiles_; // Tiles
        point vertices_[4];       // Container vertices
        uint size_;               // Number of tiles in a side

        std::default_random_engine generator_; // For random values

    public:

        // Create the map centered with the max width or height available inside a square
        map(const uint size, const double screenWidth, const double screenHeight, const double percent = 0.9, const uint seed = 0);
        virtual ~map();

        // Draw all the tiles
        void draw() const;

        // Generate all map elements
        void generateScenario(const uint rivers, const uint min_size_river);

        // Make all tiles neutral land
        void neutralizeAllTiles();

    private:

        // Generate a river
        bool generateRiver(const uint start_tile, const dir direction, const uint min_size);

        // Return the adjacent tile position in a direction
        int getAdjacentTilePos(const uint tile_pos, const dir direction) const;

        // Test if two tiles are adjacent by the sides (NOT THE VERTICES)
        bool isAdjacent(const uint tile_pos_1, const uint tile_pos_2) const;

        // Test if a tile is adjacent by the sides (NOT THE VERCITES) to any of the tiles in a vector. Taking into account a possible exception
        bool isAdjacentToAnyInVector(const uint tile_pos1, const std::vector<int> v, const int tile_pos_exception) const;
};

#endif
