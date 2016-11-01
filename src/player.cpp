#include "../include/player.hpp"

player::player():
    pos_(nullptr)
{}

player::player(tile* position):
    pos_(position)
{

}

player::~player(){}

void player::set_player(tile* x){
    move(x);
}

uint player::a_star_step(){
    return 0;
} //Vicky

void player::move(tile *next_pos){
    tile *t = next_pos;
    pos_->containsPlayer(false);
    next_pos->containsPlayer(true);
    pos_=next_pos;
}
