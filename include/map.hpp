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
#include <algorithm>
#include "common.hpp"
#include "utility.hpp"
#include "tile.hpp"

class map {

    const uint SENTINEL_MAX =  20; // Prevent infinite loops when generating the sceneario

    private:

        std::default_random_engine generator_; // For random values
        std::vector<tile> tiles_;              // Tiles
        double tiles_separation_;              // Separation between tiles (%)
        uint size_;                            // Number of tiles in the side

    public:

        map(const uint size, const double separation, const uint seed = 0);
        virtual ~map();

        // Append the map's vertices points to a vector
        void appendVertices(std::vector<ALLEGRO_VERTEX> &v, const double cx, const double cy, const double width, const double max_x, const double max_y) const;

        // Generate map elements
        void generate(void);

        // Make all tiles neutral
        void neutralizeAllTiles();

        // Access a tile
        tile *accessTile(const uint row, const uint col);

        // Access a tile's friend
        tile *accessTile(const uint row, const uint col, const dir direction);

        void checkClick();
};

#endif
