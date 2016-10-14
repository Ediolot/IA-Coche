#include "../include/tile.hpp"

////////////////////////////////////////////////////////////////////////////////
#include <iostream>
tile::tile(const bool is_border):
    neighbors_(4, nullptr),
    adjacents_(4, nullptr),
    color_(),
    is_border_(is_border),
    tile_type_(0)
{
    color_ = NEUTRAL_TILE_COLOR;
}

////////////////////////////////////////////////////////////////////////////////

tile::~tile()
{}

////////////////////////////////////////////////////////////////////////////////

void tile::addFriend(tile *n, const dir direction)
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

std::vector<ALLEGRO_VERTEX> tile::draw(const double cx, const double cy, const double width, const double border) const
{
    // The tile is drawed using two triangles
    std::vector<ALLEGRO_VERTEX> triangles(6);

    double border_px = border*width;
    double width_2   = width/2;

    triangles[0] = (ALLEGRO_VERTEX){ cx - width_2 + border_px, cy                      , 0, 0, 0, color_};
    triangles[1] = (ALLEGRO_VERTEX){ cx + width_2 - border_px, cy                      , 0, 0, 0, color_};
    triangles[2] = (ALLEGRO_VERTEX){ cx                      , cy + width_2 - border_px, 0, 0, 0, color_};
    triangles[3] = (ALLEGRO_VERTEX){ cx - width_2 + border_px, cy                      , 0, 0, 0, color_};
    triangles[4] = (ALLEGRO_VERTEX){ cx + width_2 - border_px, cy                      , 0, 0, 0, color_};
    triangles[5] = (ALLEGRO_VERTEX){ cx                      , cy - width_2 + border_px, 0, 0, 0, color_};

    return triangles;
}

////////////////////////////////////////////////////////////////////////////////

void tile::setColor(ALLEGRO_COLOR color)
{
    tile_type_ = 1;
    color_ = color;
}

////////////////////////////////////////////////////////////////////////////////

bool tile::isBorder() const
{
    return is_border_;
}

////////////////////////////////////////////////////////////////////////////////
