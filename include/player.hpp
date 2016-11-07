#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "tile.hpp"
#include "common.hpp"
#include "AStarTray.hpp"
#include <iostream> // TODO remove
#include <cmath>
#include <set>
#include <vector>

class player {

    private:

        tile *pos_;
        tile *chest_;

        bool AStar_init_;

        std::multiset<AStarTray> open_set_;
        std::multiset<AStarTray> closed_set_;

    public:

        player();
        player(tile *position, tile *chest_);
        virtual ~player();

        void setPlayer(tile* x, tile *chest_ = nullptr);
        void move(tile *next_pos);

        uint AStarStep();
        void resetAStar(tile *p, tile *t);

    private:

        void insertInClosedSet(AStarTray &t);
        void insertInOpenSet(AStarTray &t);
        double findInClosedSet(const AStarTray &t) const;
        void deleteFromOpenSet(std::multiset<AStarTray>::iterator it);
};

/*
# Uint que devuevle:
    0 -> No ha acabado
    1 -> No hay solución
    2 -> Solución encontrada

# No hay solución
# Analizar los distintos tamaños (Redimiento, etc)
*/

#endif
