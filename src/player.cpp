#include "../include/player.hpp"

player::player(tile* position):
  pos_(position)
  {

  }

uint player::a_star_step(){
    return 0;
} //Vicky

void player::move(tile *next_pos){
    tile *t = next_pos;
    if(pos_->containsPlayer()==true){
        if(next_pos->containsPlayer()==false){
            pos_->containsPlayer(false);
            pos_= next_pos;
            pos_->containsPlayer(true);

        }
    }

}
