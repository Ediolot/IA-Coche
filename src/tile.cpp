#include "../include/tile.hpp"

////////////////////////////////////////////////////////////////////////////////
#include <iostream>
tile::tile(const point v[4], const bool is_border):
    vertices_(),
    color_(),
    is_border_(is_border)
{
    vertices_[0] = v[0];
    vertices_[1] = v[1];
    vertices_[2] = v[2];
    vertices_[3] = v[3];
    color_ = NEUTRAL_TILE_COLOR;
}

////////////////////////////////////////////////////////////////////////////////

tile::~tile()
{}

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
