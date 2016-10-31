#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "tile.hpp"

class player {

private:
  tile *pos_;

public:
  player(tile *position);
  virtual ~player();
  uint a_star_step();
  void move();

};

#endif
