#include "../include/map.hpp"

////////////////////////////////////////////////////////////////////////////////

map::map(const uint rows, const uint cols, const double separation, const uint seed):
    generator_(seed ? seed : std::time(nullptr)),
    tiles_(rows*cols),
    tiles_separation_(separation),
    rows_(rows),
    cols_(cols),
    cx_(0),
    cy_(0),
    tile_size_(0)
{
    for (uint i=0; i<rows_; ++i)
        for (uint j=0; j<cols_; ++j)
        {
            tiles_[i*cols_+j].addFriend( accessTile(i, j, dir::UP_RIGHT)  , dir::UP_RIGHT);
            tiles_[i*cols_+j].addFriend( accessTile(i, j, dir::DOWN_LEFT) , dir::DOWN_LEFT);
            tiles_[i*cols_+j].addFriend( accessTile(i, j, dir::UP_LEFT)   , dir::UP_LEFT);
            tiles_[i*cols_+j].addFriend( accessTile(i, j, dir::DOWN_RIGHT), dir::DOWN_RIGHT);

            tiles_[i*cols_+j].addFriend( accessTile(i, j, dir::RIGHT), dir::RIGHT );
            tiles_[i*cols_+j].addFriend( accessTile(i, j, dir::UP)   , dir::UP);
            tiles_[i*cols_+j].addFriend( accessTile(i, j, dir::LEFT) , dir::LEFT);
            tiles_[i*cols_+j].addFriend( accessTile(i, j, dir::DOWN) , dir::DOWN);
        }
}

////////////////////////////////////////////////////////////////////////////////

map::~map()
{}

////////////////////////////////////////////////////////////////////////////////

void map::appendVertices(std::vector<ALLEGRO_VERTEX> &v, const double cx, const double cy, const double tile_size, const double max_x, const double max_y)
{
    tile_size_ = tile_size;
    cx_ = cx;
    cy_ = cy;

    const double width = tile_size_*cols_;
    const double height = tile_size_*rows_;
    const double left_corner_x = cx_ - (width/2)  + tile_size_/2;
    const double top_corner_y  = cy_ - (height/2) + tile_size_/2;

    // Reserve spaces for all the tiles in the vector
    v.reserve(v.size() + 4*rows_*cols_);

    for (uint i=0; i<rows_; ++i)
        for (uint j=0; j<cols_; ++j)
        {
            double x = left_corner_x + tile_size_*j;
            double y = top_corner_y + tile_size_*i;

            tiles_[i*cols_+j].appendVertices(v, x, y, tile_size_, tiles_separation_, max_x, max_y);
        }
}

////////////////////////////////////////////////////////////////////////////////

tile *map::accessTile(const uint row, const uint col)
{
    return (row<rows_ && col<cols_) ? &tiles_[row*cols_ + col] : nullptr;
}

////////////////////////////////////////////////////////////////////////////////

tile *map::accessTile(const uint row, const uint col, const dir direction)
{
    switch (direction)
    {
        case dir::UP:         return accessTile(row-1, col  );
        case dir::DOWN:       return accessTile(row+1, col  );
        case dir::RIGHT:      return accessTile(row  , col+1);
        case dir::LEFT:       return accessTile(row  , col-1);
        case dir::UP_LEFT:    return accessTile(row-1, col-1);
        case dir::DOWN_RIGHT: return accessTile(row+1, col+1);
        case dir::UP_RIGHT:   return accessTile(row-1, col+1);
        case dir::DOWN_LEFT:  return accessTile(row+1, col-1);
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

void map::checkClick()
{
    if (mouse.isPressed(1) || mouse.isPressed(2))
    {
        const double width = tile_size_*cols_;
        const double height = tile_size_*rows_;
        const double left_corner_x = cx_ - (width/2)  + tile_size_/2;
        const double top_corner_y  = cy_ - (height/2) + tile_size_/2;
        int j = std::round((mouse.getX()-left_corner_x)/tile_size_);
        int i = std::round((mouse.getY()-top_corner_y)/tile_size_);

        tile *t;
        if (i>=0 && j>=0 && (t = accessTile(i,j)))
            t->setType(mouse.isPressed(1) ? tileType::WATER : tileType::NEUTRAL);
    }
}

////////////////////////////////////////////////////////////////////////////////

uint map::getNRows() const
{
    return rows_;
}

////////////////////////////////////////////////////////////////////////////////

uint map::getNCols() const
{
    return cols_;
}

////////////////////////////////////////////////////////////////////////////////
