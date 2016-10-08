#include "../include/tile.hpp"

////////////////////////////////////////////////////////////////////////////////
#include <iostream>
tile::tile(const std::vector<point>& v,const bool is_border):
    neighbors_(4, nullptr),
    adjacents_(4, nullptr),
    vertices_(v),
    color_(),
    is_border_(is_border)
{
    if (v.size() != 4) vertices_.clear();
    color_ = NEUTRAL_TILE_COLOR;
}

////////////////////////////////////////////////////////////////////////////////

tile::~tile()
{}

////////////////////////////////////////////////////////////////////////////////

void tile::storeFriend(tile *n, const dir direction)
{
    switch (direction)
    {
        case dir::UP:         neighbors_[0] = n; break;
        case dir::DOWN:       neighbors_[1] = n; break;
        case dir::LEFT:       neighbors_[2] = n; break;
        case dir::RIGHT:      neighbors_[3] = n; break;

        case dir::UP_LEFT:    adjacents_[0] = n; break;
        case dir::UP_RIGHT:   adjacents_[1] = n; break;
        case dir::DOWN_LEFT:  adjacents_[2] = n; break;
        case dir::DOWN_RIGHT: adjacents_[3] = n; break;
        default: break;
    }
}

////////////////////////////////////////////////////////////////////////////////

tile* tile::getFriend(const dir direction) const
{
    switch (direction)
    {
        case dir::UP:         return neighbors_[0];
        case dir::DOWN:       return neighbors_[1];
        case dir::LEFT:       return neighbors_[2];
        case dir::RIGHT:      return neighbors_[3];

        case dir::UP_LEFT:    return adjacents_[0];
        case dir::UP_RIGHT:   return adjacents_[1];
        case dir::DOWN_LEFT:  return adjacents_[2];
        case dir::DOWN_RIGHT: return adjacents_[3];
        default: return nullptr;
    }
}

////////////////////////////////////////////////////////////////////////////////

bool tile::isAdjacentTo(const tile *n) const
{
    for (const tile* i : adjacents_)
        if (i==n) return true;

    return false;
}

////////////////////////////////////////////////////////////////////////////////

void tile::draw() const
{
    // The tile is drawed using two triangles
    al_draw_filled_triangle(vertices_[0].x, vertices_[0].y, vertices_[1].x, vertices_[1].y, vertices_[2].x, vertices_[2].y, color_);
    al_draw_filled_triangle(vertices_[0].x, vertices_[0].y, vertices_[3].x, vertices_[3].y, vertices_[2].x, vertices_[2].y, color_);
}

////////////////////////////////////////////////////////////////////////////////

void tile::setColor(ALLEGRO_COLOR color)
{
    color_ = color;
}

////////////////////////////////////////////////////////////////////////////////

bool tile::isBorder() const
{
    return is_border_;
}

////////////////////////////////////////////////////////////////////////////////
