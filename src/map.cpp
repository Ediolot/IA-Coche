#include "../include/map.hpp"

////////////////////////////////////////////////////////////////////////////////

map::map():
    map(0,0,0)
{}

////////////////////////////////////////////////////////////////////////////////

map::map(const uint rows, const uint cols, const double obstacles):
    tiles_(),
    rows_(0),
    cols_(0),
    obstacles_(0),
    cx_(0),
    cy_(0),
    width_(0),
    height_(0),
    tile_size_(0),
    zoom_(1),
    last_mouse_z_(0),
    generator_()
{
    rebuild(rows, cols, obstacles);
}

////////////////////////////////////////////////////////////////////////////////

map::~map()
{}

////////////////////////////////////////////////////////////////////////////////

void map::rebuild(const uint rows, const uint cols, const double obstacles)
{
    rows_ = rows;
    cols_ = cols;

    inc_x_ = 0;
    inc_y_ = 0;
    zoom_ = 1;

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

    generate(obstacles);
    moveTo(cx_, cy_, width_, height_);
}

////////////////////////////////////////////////////////////////////////////////

void map::draw()
{
    std::vector<ALLEGRO_VERTEX> v;

    const double p_x = cx_-(rows_ - 1)*tile_size_*zoom_/2; // Left top corner coord.
    const double p_y = cy_-(cols_ - 1)*tile_size_*zoom_/2;

    // Reserve spaces for all the tiles in the vector
    v.reserve(v.size() + 4*rows_*cols_);

    for (uint i=0; i<rows_; ++i)
    {
        for (uint j=0; j<cols_; ++j)
        {
            const double x = p_x + tile_size_*j*zoom_+inc_x_;
            const double y = p_y + tile_size_*i*zoom_+inc_y_;
            const double max_x = cx_ + width_ /2;
            const double max_y = cy_ + height_/2;

            if ((x+tile_size_) >= 0     &&
                (x-tile_size_) <= max_x &&
                (y-tile_size_) <= max_y)

                tiles_[i*cols_+j].appendVertices(v, x, y, tile_size_*zoom_);
        }
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
    obstacles_ = obstacles;
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

void map::moveTo(const double cx, const double cy, const double width, const double height)
{
    double cols_size = width/rows_;
    double rows_size = height/cols_;
    tile_size_ = (width < height ? cols_size : rows_size);

    cx_ = cx;
    cy_ = cy;
    width_ = width;
    height_ = height;
}

////////////////////////////////////////////////////////////////////////////////

void map::update()
{
    if (mouse.insideBox(cx_-width_/2,cy_-height_/2,width_,height_))
    {
        zoom_ += (mouse.getZ() - last_mouse_z_)*0.1;
        zoom_ = zoom_ < 0.1 ? 0.1 : zoom_;

        if (mouse.leftDown() || mouse.rightDown())
        {
            const double p_x = cx_-(rows_ - 1)*tile_size_*zoom_/2 + inc_x_; // Left top corner coord.
            const double p_y = cy_-(cols_ - 1)*tile_size_*zoom_/2 + inc_y_;

            int j = std::round((mouse.getX()-p_x)/(tile_size_*zoom_));
            int i = std::round((mouse.getY()-p_y)/(tile_size_*zoom_));

            tile *t;
            if (i>=0 && j>=0 && (t = accessTile(i,j)))
                t->setType(mouse.leftDown() ? tileType::WATER : tileType::NEUTRAL);
        }

        if (keysPress[ALLEGRO_KEY_W]) inc_y_ += scrollSpeed/FPS;
        if (keysPress[ALLEGRO_KEY_S]) inc_y_ -= scrollSpeed/FPS;
        if (keysPress[ALLEGRO_KEY_A]) inc_x_ += scrollSpeed/FPS;
        if (keysPress[ALLEGRO_KEY_D]) inc_x_ -= scrollSpeed/FPS;
    }

    last_mouse_z_ = mouse.getZ();
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
