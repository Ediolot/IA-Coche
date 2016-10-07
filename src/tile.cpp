#include "../include/tile.hpp"

tile::tile(const point v[4]):
    vertices_()
{
    vertices_[0] = v[0];
    vertices_[1] = v[1];
    vertices_[2] = v[2];
    vertices_[3] = v[3];
}

tile::~tile()
{}

void tile::draw() const
{
    // The tile is drawed using two triangles
    al_draw_filled_triangle(vertices_[0].x, vertices_[0].y, vertices_[1].x, vertices_[1].y, vertices_[2].x, vertices_[2].y, ORANGE);
    al_draw_filled_triangle(vertices_[0].x, vertices_[0].y, vertices_[3].x, vertices_[3].y, vertices_[2].x, vertices_[2].y, ORANGE);
}
