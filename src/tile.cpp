#include "../include/tile.hpp"

////////////////////////////////////////////////////////////////////////////////
#include <iostream>
tile::tile():
    neighbors_(4, nullptr),
    adjacents_(4, nullptr),
    tile_color_(NEUTRAL_TILE_COLOR),
    tile_type_(tileType::NEUTRAL)
{}

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

void tile::appendVertices(std::vector<ALLEGRO_VERTEX> &v, const double cx, const double cy, const double width, const double border, const double max_x, const double max_y) const
{
    // The tile is drawed using two triangles
    double border_px = border*width;
    double width_2   = width/2;

    ALLEGRO_VERTEX points[4] = {
        {(cx - width_2)+border_px, (cy          )          , 0.0, 0.0, 0.0, tile_color_},
        {(cx          )          , (cy - width_2)+border_px, 0.0, 0.0, 0.0, tile_color_},
        {(cx + width_2)-border_px, (cy          )          , 0.0, 0.0, 0.0, tile_color_},
        {(cx          )          , (cy + width_2)-border_px, 0.0, 0.0, 0.0, tile_color_}
    };

    if (points[0].y >= 0 && points[1].y <= max_y && points[0].x <= max_x && points[2].x >= 0)
    {
        v.push_back(points[0]);
        v.push_back(points[1]);
        v.push_back(points[2]);
    }

    if (points[3].y >= 0 && points[0].y <= max_y && points[0].x <= max_x && points[2].x >= 0)
    {
        v.push_back(points[0]);
        v.push_back(points[2]);
        v.push_back(points[3]);
    }
}

////////////////////////////////////////////////////////////////////////////////

void tile::setType(const tileType type)
{
    tile_type_ = type;

    switch (type)
    {
        case tileType::WATER: tile_color_ = WATER_TILE_COLOR;   break;
        default:              tile_color_ = NEUTRAL_TILE_COLOR; break;
    }
}

////////////////////////////////////////////////////////////////////////////////

bool tile::isBorder() const
{
    return isAdjacentTo(nullptr);
}

////////////////////////////////////////////////////////////////////////////////
