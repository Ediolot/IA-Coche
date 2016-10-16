#include "../include/map.hpp"

////////////////////////////////////////////////////////////////////////////////

map::map(const uint size, const double separation, const uint seed):
    generator_(seed ? seed : std::time(nullptr)),
    tiles_(size*size),
    tiles_separation_(separation),
    size_(size)
{
    // TODO comprobar
    for (uint i=0; i<tiles_.size(); ++i)
    {
        tiles_[i].addFriend( accessTile(i / size_, i % size_, dir::UP_RIGHT)        , dir::UP_RIGHT       );
        tiles_[i].addFriend( accessTile(i / size_, i % size_, dir::DOWN_LEFT)      , dir::DOWN_LEFT     );
        tiles_[i].addFriend( accessTile(i / size_, i % size_, dir::UP_LEFT)      , dir::UP_LEFT     );
        tiles_[i].addFriend( accessTile(i / size_, i % size_, dir::DOWN_RIGHT)     , dir::DOWN_RIGHT    );

        tiles_[i].addFriend( accessTile(i / size_, i % size_, dir::RIGHT)  , dir::RIGHT );
        tiles_[i].addFriend( accessTile(i / size_, i % size_, dir::UP)   , dir::UP);
        tiles_[i].addFriend( accessTile(i / size_, i % size_, dir::LEFT) , dir::LEFT);
        tiles_[i].addFriend( accessTile(i / size_, i % size_, dir::DOWN), dir::DOWN);
    }
}

////////////////////////////////////////////////////////////////////////////////

map::~map()
{}

////////////////////////////////////////////////////////////////////////////////

void map::appendVertices(std::vector<ALLEGRO_VERTEX> &v, const double cx, const double cy, const double width, const double max_x, const double max_y) const
{
    const double delta         = width / size_;
    const double delta_2       = delta/2;
    const double left_corner_x = cx - (width/2) + delta_2;
    const double top_corner_y  = cy - (width/2) + delta_2;

    // Reserve spaces for all the tiles in the vector
    v.reserve(v.size() + 4*size_*size_);

    for (uint i=0; i<size_; ++i)
        for (uint j=0; j<size_; ++j)
        {
            double x = left_corner_x + delta*j;
            double y = top_corner_y + delta*i;

            tiles_[0*size_+j].appendVertices(v, x, y, delta, tiles_separation_, max_x, max_y);
        }
}

////////////////////////////////////////////////////////////////////////////////

tile *map::accessTile(const uint row, const uint col)
{
    return (row<size_ && col<size_) ? &tiles_[row*size_ + col] : nullptr;
}

////////////////////////////////////////////////////////////////////////////////

tile *map::accessTile(const uint row, const uint col, const dir direction)
{
    switch (direction)
    {
        case dir::UP:         return accessTile(row-1, col+1);
        case dir::DOWN:       return accessTile(row+1, col-1);
        case dir::RIGHT:      return accessTile(row+1, col+1);
        case dir::LEFT:       return accessTile(row-1, col-1);
        case dir::UP_LEFT:    return accessTile(row-1, col  );
        case dir::DOWN_RIGHT: return accessTile(row+1, col  );
        case dir::UP_RIGHT:   return accessTile(row  , col+1);
        case dir::DOWN_LEFT:  return accessTile(row  , col-1);
        default: return nullptr;
    }
}

////////////////////////////////////////////////////////////////////////////////

void map::generate()
{}

////////////////////////////////////////////////////////////////////////////////


void map::neutralizeAllTiles()
{
    for (tile &i : tiles_) i.setType(tileType::NEUTRAL);
}

////////////////////////////////////////////////////////////////////////////////
