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
#include "mazeGenerator.hpp"
#include "images.hpp"

class map {

    const uint SENTINEL_MAX = 20; // Prevent infinite loops when generating the sceneario

    private:

        std::vector<tile> tiles_;  // Tiles
        uint rows_;
        uint cols_;
        double obstacles_;

        tile *origin_;
        tile *goal_;

        double cx_;
        double cy_;
        double width_;
        double height_;
        double tile_size_;

        double zoom_;
        double inc_x_;
        double inc_y_;
        double last_mouse_z_;

        mazeGenerator generator_;

    public:

        map();
        map(const uint rows, const uint cols, const double obstacles);
        virtual ~map();

        void rebuild(const uint rows, const uint cols, const double obstacles);

        void draw();

        // Generate map elements
        void generate(const double obstacles);

        // Make all tiles neutral
        void neutralizeAllTiles();

        // Access a tile
        tile *accessTile(const uint row, const uint col);

        // Access a tile's friend
        tile *accessTile(const uint row, const uint col, const dir direction);

        uint getNRows() const;
        uint getNCols() const;

        void moveTo(const double cx, const double cy, const double width, const double height);
        void update();
};

#endif
