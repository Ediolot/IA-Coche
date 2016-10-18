#include "../include/map.hpp"

////////////////////////////////////////////////////////////////////////////////

map::map(const uint rows, const uint cols, const double tile_size, const double obstacles):
    tiles_(),
    rows_(0),
    cols_(0),
    cx_(0),
    cy_(0),
    tile_size_(0),
    generator_()
{
    rebuild(rows, cols, tile_size);
    generate(obstacles);
}

////////////////////////////////////////////////////////////////////////////////

map::~map()
{}

////////////////////////////////////////////////////////////////////////////////

void map::rebuild(const uint rows, const uint cols)
{
    rows_ = rows;
    cols_ = cols;

    tiles_.clear();
    tiles_.resize(rows*cols);
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

void map::draw()
{
    std::vector<ALLEGRO_VERTEX> v;
    const double left_corner_x = cx_ - (width_/2)  + tile_size_/2;
    const double top_corner_y  = cy_ - (height_/2) + tile_size_/2;

    // Reserve spaces for all the tiles in the vector
    v.reserve(v.size() + 4*rows_*cols_);

    for (uint i=0; i<rows_; ++i)
        for (uint j=0; j<cols_; ++j)
        {
            const double x = left_corner_x + tile_size_*j;
            const double y = top_corner_y  + tile_size_*i;

            if ((x+tiles_size_/2) >= 0     &&
                (y+tiles_size_/2) <= max_y &&
                (x-tiles_size_/2) <= max_x &&
                (y-tiles_size_/2) >= 0)

                tiles_[i*cols_+j].appendVertices(v, x, y, tile_size_);
        }

    al_draw_prim(v.data(), nullptr, sprute_image, 0, v.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
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

void map::generate(const double obstacles)
{
    generator_.randomize(rows_, cols_, obstacles);

    for (uint i=0; i<(rows_*cols_); ++i)
        tiles_[i].setType(generator_.getPos(i/cols_, i%cols_) ? tileType::WATER : tileType::NEUTRAL);
}

////////////////////////////////////////////////////////////////////////////////


void map::neutralizeAllTiles()
{
    for (tile &i : tiles_) i.setType(tileType::NEUTRAL);
}

////////////////////////////////////////////////////////////////////////////////

void map::update(const double cx, const double cy, const double max_x, const double max_y, const double tile_size)
{
    tile_size_ = tile_size;
    width_  = tile_size_*cols_;
    height_ = tile_size_*rows_;
    cx_ = cx;
    cy_ = cy;

    if (mouse.isPressed(1) || mouse.isPressed(2))
    {
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
