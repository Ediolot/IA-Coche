/*
    REPRESENTS THE TILES MAP

    Container with multiple tiles elements. Each tile is a diamond shape.

    TILES ADJACENCY & DIRECTIONS:

                             #
                           #   #
                         #       #
                       #           #
                     #      UP       #
                   #   #           #   #
                 #       #       #       #
               #           #   #           #
             #    UP_LEFT    #   UP_RIGHT    #
           #   #           #   #           #   #
         #       #       #       #       #       #
       #           #   #           #   #           #
     #     LEFT      #     CENTER    #     RIGHT     #
       #           #   #           #   #           #
         #       #       #       #       #       #
           #   #           #   #           #   #
             #   DOWN_LEFT   #  DOWN_RIGHT   #
               #           #   #           #
                 #       #       #       #
                   #   #           #   #
                     #     DOWN      #
                       #           #
                         #       #
                           #   #
                             #

     Tiles UP_LEFT, UP_RIGHT, DOWN_LEFT & DOWN_RIGHT are adjacent to the center. The others are NOT.
     Tiles UP, LEFT, DOWN & RIGHT are neighbors to the center. The others are NOT.
     All of them are friends to the center.
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

class map {

    const uint SENTINEL_MAX =  20; // Prevent infinite loops when generating the sceneario

    private:

        std::default_random_engine generator_; // For random values
        std::vector<tile> tiles_;              // Tiles
        double separation_;                    // Separation between tiles (%)
        uint size_;                            // Number of tiles in the side

    public:

        // TODO
        map(const uint size, const double separation, const uint seed = 0);
        virtual ~map();

        // Draw all the tiles
        std::vector<ALLEGRO_VERTEX> draw(const double cx, const double cy, const double width, const double max_x, const double min_x, const double max_y, const double min_y) const;

        // Generate all map elements
        void generateScenario(const uint rivers, const uint min_size_river, const bool accumulative_rivers);

        // Make all tiles neutral land
        void neutralizeAllTiles();

        tile *accessTile(const uint row, const uint col);
        tile *accessTile(const uint row, const uint col, const dir direction);

    private:

        // Generate a river
        bool generateRiver(const uint start_tile, const dir direction, const uint min_size, const bool accumulative);

        // Test if a tile is adjacent by the sides to any of the tiles in a vector. Taking into account a possible exception
        bool isAdjacentToAnyInVector(const tile* test, const std::vector<tile*>& v, const tile* test_exception) const;
};

#endif
