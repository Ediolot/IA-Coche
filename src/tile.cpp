#include "../include/tile.hpp"

////////////////////////////////////////////////////////////////////////////////

tile::tile():
    neighbors_(4, nullptr),
    adjacents_(4, nullptr),
    tile_type_(tile::type::NEUTRAL),
    contains_player_(false)
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

void tile::appendVertices(std::vector<ALLEGRO_VERTEX> &v, const double cx, const double cy, const double width) const
{
    // The tile is drawed using two triangles
    double width_2 = width/2;

    float texture_x, texture_y;

    if (containsPlayer())
    {
        texture_x = 0;
        texture_y = 32;
    }
    else
    {
        switch (tile_type_)
        {
            case tile::type::WALL:    texture_x =  0; texture_y =  0; break;
            case tile::type::MONSTER: texture_x =  0; texture_y = 64; break;
            case tile::type::CHEST:   texture_x =  0; texture_y = 96; break;
            case tile::type::ORIGIN:  texture_x = 33; texture_y = 32; break;
            default:                  texture_x = 33; texture_y =  0; break;
        }
    }

    ALLEGRO_VERTEX points[8] = {
        {float(cx - width_2), float(cy - width_2), 0.f, texture_x   , texture_y   , al_map_rgb(255,255,255)},
        {float(cx + width_2), float(cy - width_2), 0.f, texture_x+31, texture_y   , al_map_rgb(255,255,255)},
        {float(cx + width_2), float(cy + width_2), 0.f, texture_x+31, texture_y+31, al_map_rgb(255,255,255)},
        {float(cx - width_2), float(cy + width_2), 0.f, texture_x   , texture_y+31, al_map_rgb(255,255,255)}
    };

    v.push_back(points[3]);
    v.push_back(points[2]);
    v.push_back(points[0]);
    v.push_back(points[1]);
    v.push_back(points[2]);
    v.push_back(points[0]);
}

////////////////////////////////////////////////////////////////////////////////

void tile::setType(const tile::type type)
{
    tile_type_ = type;
}

////////////////////////////////////////////////////////////////////////////////

bool tile::isWall() const
{
    return tile_type_ == tile::type::WALL;
}

////////////////////////////////////////////////////////////////////////////////

bool tile::isMonster() const
{
    return tile_type_ == tile::type::MONSTER;
}

////////////////////////////////////////////////////////////////////////////////

bool tile::isChest() const
{
    return tile_type_ == tile::type::CHEST;
}

////////////////////////////////////////////////////////////////////////////////

bool tile::containsPlayer() const
{
    return contains_player_;
}

////////////////////////////////////////////////////////////////////////////////

void tile::containsPlayer(bool set)
{
    contains_player_ = set;
}

////////////////////////////////////////////////////////////////////////////////

bool tile::isOrigin() const
{
    return tile_type_ == tile::type::ORIGIN;
}

////////////////////////////////////////////////////////////////////////////////

bool tile::isBorder() const
{
    return isAdjacentTo(nullptr);
}

////////////////////////////////////////////////////////////////////////////////
