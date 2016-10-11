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

void tile::draw(const double cx, const double cy, const double width) const
{
    // The tile is drawed using two triangles

    point vertices[4] = {
        {cx - width/2, cy},
        {cx, cy - width/2},
        {cx + width/2, cy},
        {cx, cy + width/2}
    };

    drawQUAD(vertices, color_);

/* NOTE Draw borders in the tile. Unused
    double s = side_*0.2;
    double frac = (vertices_[0].y - vertices_[1].y)/(vertices_[0].x - vertices_[1].x);
    double x = s / std::sqrt(1 + frac*frac);
    double y = std::sqrt(s*s-x*x);

    if (!getFriend(dir::DOWN_LEFT) || !(getFriend(dir::DOWN_LEFT)->tile_type_))
    {
        // DOWN_LEFT border
        al_draw_filled_triangle(vertices_[0].x, vertices_[0].y, vertices_[0].x+x, vertices_[0].y-y, vertices_[3].x, vertices_[3].y, NEUTRAL_TILE_COLOR);
        al_draw_filled_triangle(vertices_[0].x+x, vertices_[0].y-y, vertices_[3].x, vertices_[3].y, vertices_[3].x+x, vertices_[3].y-y, NEUTRAL_TILE_COLOR);
    }

    if (!getFriend(dir::DOWN_RIGHT) || !(getFriend(dir::DOWN_RIGHT)->tile_type_))
    {
        // DOWN_RIGHT border
        al_draw_filled_triangle(vertices_[3].x-x, vertices_[3].y-y, vertices_[3].x, vertices_[3].y, vertices_[2].x, vertices_[2].y, NEUTRAL_TILE_COLOR);
        al_draw_filled_triangle(vertices_[3].x-x, vertices_[3].y-y, vertices_[2].x-x, vertices_[2].y-y, vertices_[2].x, vertices_[2].y, NEUTRAL_TILE_COLOR);
    }

    if (!getFriend(dir::UP_LEFT) || !(getFriend(dir::UP_LEFT)->tile_type_))
    {
        // UP_LEFT border
        al_draw_filled_triangle(vertices_[0].x, vertices_[0].y, vertices_[1].x, vertices_[1].y, vertices_[0].x+x, vertices_[0].y+y, NEUTRAL_TILE_COLOR);
        al_draw_filled_triangle(vertices_[0].x+x, vertices_[0].y+y, vertices_[1].x, vertices_[1].y, vertices_[1].x+x, vertices_[1].y+y, NEUTRAL_TILE_COLOR);
    }

    if (!getFriend(dir::UP_RIGHT) || !(getFriend(dir::UP_RIGHT)->tile_type_))
    {
        // UP_RIGHT border
        al_draw_filled_triangle(vertices_[1].x, vertices_[1].y, vertices_[2].x, vertices_[2].y, vertices_[2].x-x, vertices_[0].y+y, NEUTRAL_TILE_COLOR);
        al_draw_filled_triangle(vertices_[1].x-x, vertices_[1].y+y, vertices_[1].x, vertices_[1].y, vertices_[2].x-x, vertices_[2].y+y, NEUTRAL_TILE_COLOR);
    }
*/
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
