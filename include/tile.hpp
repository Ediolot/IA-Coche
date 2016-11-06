/*
    REPRESENTS A TILE
*/

#ifndef TILE_HPP
#define TILE_HPP

#include <allegro5/allegro_primitives.h>
#include <vector>
#include <cmath>
#include <utility>
#include <cstdlib>
#include "fonts.hpp"
#include "common.hpp"
#include "utility.hpp"

class tile {

    public:

        enum type {
            NEUTRAL,
            WALL,
            MONSTER1,
            MONSTER2,
            MONSTER3,
            MONSTER4,
            CHEST,
            ORIGIN
        };

    private:

        std::vector<tile*> neighbors_;
        std::vector<tile*> adjacents_;

        tile::type tile_type_;

        bool contains_player_;

        double x_; // Tile's position in relation with other tiles in the map
        double y_;

    public:

        tile(const double x = 0, const double y = 0);
        virtual ~tile();

        // Add a tile's friend
        void addFriend(tile *n, const dir direction);

        // Get a tile's friend
        tile* getFriend(const dir direction) const;

        // Tell's if a tile is adjacent to another
        bool isAdjacentTo(const tile *n) const;

        // Check if is a border tile
        bool isBorder() const;

        // Check if the tile's type is wall
        bool isWall() const;

        // Check if the tile's type is monster
        bool isMonster() const;

        // Check if the tile's type is chest
        bool isChest() const;

        // Check if the tile's type is origin
        bool isOrigin() const;

        // Check if the tile contains the player
        bool containsPlayer() const;

        // Set if the tile contains the player
        void containsPlayer(bool set);

        // Tile's x position in relation with the othter tiles of the map
        uint getX() const;

        // Tile's y position in relation with the othter tiles of the map
        uint getY() const;

        // Append the tile's vertices points to a vector
        void appendVertices(
            std::vector<ALLEGRO_VERTEX> &v,
            const double cx,
            const double cy,
            const double width
        ) const;

        // Change the tile color
        void setType(const tile::type type);

        void setRandomMonsterType();
};


#endif
