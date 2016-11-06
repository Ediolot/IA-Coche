#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "tile.hpp"
#include "common.hpp"
#include <iostream> // TODO remove

class player {

private:
  tile *pos_;
  tile *chest_;

public:
  player();
  player(tile *position, tile *chest_);
  virtual ~player();
  void setPlayer(tile* x, tile *chest_ = nullptr);
  uint AStarAtep();
  void move(tile *next_pos);
};

/*
# Para comprobar que es (ver tile.hpp)
current_ ->isWall()
current_->isMonster()

# Cuidado si es nulo
tile t* = current_->getFriend();
t == nullptr

# Mover al personaje
tile t* = casilla a la que me quiero Mover
current->containsPlayer(false);
t->containsPlayer(true);
current_ = t_;

# Uint que devuevle:
    0 -> No ha acabado
    1 -> No hay solución
    2 -> Solución encontrada

# No hay solución
# Analizar los distintos tamaños (Redimiento, etc)
*/

#endif
