/*
    REPRESENTS THE TILES MAP

    Container with multiple tiles elements. Each tile is a diamond shape.

    TILES ADJACENCY & DIRECTIONS:

    ####################################
    #            #        #            #
    #  UP_LEFT   #   UP   #  UP_RIGHT  #
    #            #        #            #
    ####################################
    #            #        #            #
    #    LEFT    # CENTER #    RIGHT   #
    #            #        #            #
    ####################################
    #            #        #            #
    #  DOWN_LEFT #  DOWN  # DOWN_RIGHT #
    #            #        #            #
    ####################################

     Tiles UP_LEFT, UP_RIGHT, DOWN_LEFT & DOWN_RIGHT are adjacent to the center. The others are NOT.
     Tiles UP, LEFT, DOWN & RIGHT are neighbors to the center. The others are NOT.
     All of them are friends to the center.
*/

#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <ctime>
#include <algorithm>
#include <cmath>
#include "common.hpp"
#include "utility.hpp"
#include "tile.hpp"
#include "mouse.hpp"

class map {

    const uint SENTINEL_MAX = 20; // Prevent infinite loops when generating the sceneario

    private:

        std::vector<tile> tiles_;  // Tiles
        double tiles_separation_;  // Separation between tiles (%)
        uint rows_;
        uint cols_;

        double cx_;
        double cy_;
        double tile_size_;

    public:

        map(const uint rows, const uint cols, const double separation);
        virtual ~map();

        void rebuild(const uint rows, const uint cols);

        // Append the map's vertices points to a vector
        void appendVertices(std::vector<ALLEGRO_VERTEX> &v, const double cx, const double cy, const double tile_size, const double max_x, const double max_y);

        // Generate map elements
        void generate(void);

        // Make all tiles neutral
        void neutralizeAllTiles();

        // Access a tile
        tile *accessTile(const uint row, const uint col);

        // Access a tile's friend
        tile *accessTile(const uint row, const uint col, const dir direction);

        uint getNRows() const;
        uint getNCols() const;

        void checkClick();
};

#endif
