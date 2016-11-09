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
    show_(true),
    origin_(nullptr),
    goal_(nullptr),
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
    if (!rows || !cols) return;

    rows_ = rows;
    cols_ = cols;

    inc_x_ = 0;
    inc_y_ = 0;
    zoom_ = 0.98;

    tiles_.clear();
    tiles_.reserve(rows*cols);

    for (uint i=0; i<rows_; ++i)
        for (uint j=0; j<cols_; ++j)
            tiles_.push_back(tile(i, j));


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
    resize(cx_, cy_, width_, height_);
}

////////////////////////////////////////////////////////////////////////////////

void map::draw()
{
    if (!show_) return;

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

            /*if ((x+tile_size_*zoom_) >= 0     &&
                (x-tile_size_*zoom_) <= max_x &&
                (y+tile_size_*zoom_) >= 0     &&
                (y-tile_size_*zoom_) <= max_y)*/

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
    {
        if (generator_.getPos(i/cols_, i%cols_) && !(std::rand() % monsters_percent))
            tiles_[i].setRandomMonsterType();
        else
            tiles_[i].setType(generator_.getPos(i/cols_, i%cols_) ? tile::type::WALL : tile::type::NEUTRAL);
    }

    tile *t = &tiles_[generator_.randomRow()*cols_ + generator_.randomCol()];
    t->setType(tile::type::ORIGIN);
    t->containsPlayer(true);
    origin_ = t;

    while (t->containsPlayer())
        t = &tiles_[generator_.randomRow()*cols_ + generator_.randomCol()];

    t->setType(tile::type::CHEST);
    goal_ = t;

    resetPlayer();
}

////////////////////////////////////////////////////////////////////////////////


void map::clearAllTiles()
{
    for (tile &i : tiles_) {
        i.containsPlayer(false);
        i.setType(tile::type::NEUTRAL);
    }
}

////////////////////////////////////////////////////////////////////////////////

void map::resize(const double cx, const double cy, const double width, const double height)
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

player& map::getPlayer()
{
    return p1_;
}

////////////////////////////////////////////////////////////////////////////////

void map::resetPlayer()
{
    p1_.setPlayer(origin_, goal_);
    p1_.resetAStar(origin_, goal_);
    for (tile &i : tiles_) i.tint(al_map_rgb(150,150,150));
    goal_->tint(al_map_rgb(255,255,255));
    origin_->tint(al_map_rgb(255,255,255));
}

////////////////////////////////////////////////////////////////////////////////

void map::update()
{
    if (!show_)
    {
        last_mouse_z_ = mouse.getZ();
        return;
    }

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
            if (i>=0 && j>=0 && mouse.leftDown() && (t = accessTile(i,j)) && !t->containsPlayer())
            {
                std::cout << "tile is: " << t->getX() << "," << t->getY() << std::endl;
                if (keysPress[ALLEGRO_KEY_3] && !t->isOrigin())
                {
                    if (goal_) goal_->setType(tile::type::NEUTRAL);
                    goal_ = t;
                    goal_->setType(tile::type::CHEST);
                    resetPlayer();
                }
                else if (keysPress[ALLEGRO_KEY_2] && !t->isChest())
                {
                    if (origin_) origin_->setType(tile::type::NEUTRAL);
                    origin_ = t;
                    origin_->setType(tile::type::ORIGIN);
                }
                else if (!t->isOrigin() && !t->isChest())
                {
                         if (keysPress[ALLEGRO_KEY_1]) t->setType(tile::type::WALL);
                    else if (keysPress[ALLEGRO_KEY_4]) t->setType(tile::type::MONSTER1);
                    else if (keysPress[ALLEGRO_KEY_5]) t->setType(tile::type::MONSTER2);
                    else if (keysPress[ALLEGRO_KEY_6]) t->setType(tile::type::MONSTER3);
                    else if (keysPress[ALLEGRO_KEY_7]) t->setType(tile::type::MONSTER4);
                    else                               t->setType(tile::type::NEUTRAL);
                }
            }
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

void map::show(bool show)
{
    show_ = show;
}

////////////////////////////////////////////////////////////////////////////////

void map::hide()
{
    show_ = false;
}

////////////////////////////////////////////////////////////////////////////////
