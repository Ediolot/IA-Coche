#include "../include/player.hpp"

player::player():
    player(nullptr, nullptr)
{}

player::player(tile* position, tile *chest):
    pos_(position),
    chest_(chest)
{
}

player::~player(){}

void player::setPlayer(tile* x, tile *chest){
    if (chest) chest_ = chest;
    pos_ = x;
    move(pos_);

    if (pos_)   std::cout << "Player at: " << pos_->getX() << "," << pos_->getY() << std::endl;
    if (chest_) std::cout << "Chest at: " << chest_->getX() << "," << chest_->getY() << std::endl;
}

uint player::AStarStep(){
    if (pos_->getFriend(dir::RIGHT)->isWall()) return 1;
    move(pos_->getFriend(dir::RIGHT));
    return 0;
} //Vicky

void player::move(tile *next_pos){
    tile *t = next_pos;
    if (next_pos)
    {
        pos_->containsPlayer(false);
        next_pos->containsPlayer(true);
        pos_=next_pos;
    }
}
