#include "../include/map.hpp"

////////////////////////////////////////////////////////////////////////////////

map::map(const uint size, const double screenWidth, const double screenHeight, const double percent, const uint seed):
    tiles_(),
    vertices_(),
    size_(size),
    generator_(seed ? seed : std::time(nullptr))
{
    double width  = screenWidth * percent;
    double height = screenHeight * percent;
    double square_side = width < height ? width : height;
    double side = 0.7071 * square_side;

    // Set the container's vertices

    vertices_[0].set((screenWidth - square_side) / 2, screenHeight / 2);
    vertices_[2].set((screenWidth + square_side) / 2, screenHeight / 2);

    vertices_[1].set(screenWidth / 2, (screenHeight - square_side) / 2);
    vertices_[3].set(screenWidth / 2, (screenHeight + square_side) / 2);

    // Create tiles

    double tile_side = side / size;
    double delta   = 0.7071 * tile_side;

    point tilePoints[4];

    for (uint i=0; i<size; ++i)
    {
        for (uint j=0; j<size; ++j)
        {
            double x = vertices_[0].x + i*delta + j*delta;
            double y = vertices_[0].y + i*delta - j*delta;

            tilePoints[0].set(x + delta*(BORDER  ), y                   );
            tilePoints[1].set(x + delta           , y + delta*(BORDER-1));
            tilePoints[2].set(x + delta*(2-BORDER), y                   );
            tilePoints[3].set(x + delta           , y + delta*(1-BORDER));

            tiles_.emplace_back(tilePoints, i==0 || j==0 || (i+1)>=size_ || (j+1)>=size_);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

map::~map()
{}

////////////////////////////////////////////////////////////////////////////////

void map::draw() const
{
    for (auto &i : tiles_) i.draw();
}

////////////////////////////////////////////////////////////////////////////////

void map::generateScenario(const uint rivers, const uint min_size_river)
{
    std::uniform_int_distribution<int> random_switch(0,3);
    std::uniform_int_distribution<int> random_tile(0,size_-1);
    uint rivers_made = 0;

    while (rivers_made < rivers)
    {
        dir river_direction;
        switch (random_switch(generator_))
        {
            case 0: river_direction = dir::UP;    break;
            case 1: river_direction = dir::DOWN;  break;
            case 2: river_direction = dir::LEFT;  break;
            case 3: river_direction = dir::RIGHT; break;
            default: break;
        }

        uint start_tile;
        switch (random_switch(generator_))
        {
            case 0: start_tile = random_tile(generator_)*size_ + size_-1; break;
            case 1: start_tile = random_tile(generator_)*size_; break;
            case 2: start_tile = (size_-1)*size_ + random_tile(generator_); break;
            case 3: start_tile = random_tile(generator_); break;
        }

        if (generateRiver(start_tile,river_direction,min_size_river))
            rivers_made++;
    }
}

////////////////////////////////////////////////////////////////////////////////

bool map::generateRiver(const uint start_tile, const dir direction, const uint min_size)
{
    std::normal_distribution<double> normal(0.0,0.3);
    std::vector<int> river_tiles;

    double target_angle;
    switch (direction)
    {
        case dir::UP:    target_angle =  90.0; break;
        case dir::DOWN:  target_angle = 270.0; break;
        case dir::LEFT:  target_angle = 180.0; break;
        case dir::RIGHT: target_angle =   0.0; break;
        default: return false;
    }

    int target_tile  = -1;
    int current_tile = start_tile;

    river_tiles.push_back(start_tile);

    int maxit = 100;

    for (uint current_size = 0; current_size < min_size || target_tile>=0; ++current_size)
    {
        int it = 0;
        do
        {
            double desviation = normal(generator_)*135.0;
            double new_angle = target_angle + desviation;
            while (new_angle > 360) new_angle -= 360;

            dir target_direction;

            if (new_angle < 90)
                target_direction = dir::UP_RIGHT;
            else if (new_angle < 180)
                target_direction = dir::UP_LEFT;
            else if (new_angle < 270)
                target_direction = dir::DOWN_LEFT;
            else
                target_direction = dir::DOWN_RIGHT;

            target_tile = getAdjacentTilePos(current_tile, target_direction);

            if (++it==maxit) return false;

        } while ((target_tile<0 && current_size < min_size) || isAdjacentToAnyInVector(target_tile, river_tiles, current_tile));

        river_tiles.push_back(target_tile);
        current_tile = target_tile;
    }

    for (int i : river_tiles)
        if (i!=-1) tiles_[i].setColor(RIVER_TILE_COLOR);

    return true;
}

////////////////////////////////////////////////////////////////////////////////

void map::neutralizeAllTiles()
{
    for (auto &i : tiles_) i.setColor(NEUTRAL_TILE_COLOR);
}

////////////////////////////////////////////////////////////////////////////////

int map::getAdjacentTilePos(const uint tile_pos, const dir direction) const
{
    int i = tile_pos / size_;
    int j = tile_pos % size_;

    switch (direction)
    {
        case dir::UP:         i = (i-1); j = (j+1); break;
        case dir::DOWN:       i = (i+1); j = (j-1); break;
        case dir::LEFT:       i = (i-1); j = (j-1); break;
        case dir::RIGHT:      i = (i+1); j = (j+1); break;
        case dir::UP_LEFT:    i = (i-1);            break;
        case dir::UP_RIGHT:              j = (j+1); break;
        case dir::DOWN_LEFT:             j = (j-1); break;
        case dir::DOWN_RIGHT: i = (i+1);            break;
        default: break;
    }

    if (i<0 || j<0 || uint(i)>=size_ || uint(j)>=size_) // No existe la casilla
        return -1;
    else
        return i*size_+j;
}

////////////////////////////////////////////////////////////////////////////////

bool map::isAdjacent(const uint tile_pos_1, const uint tile_pos_2) const
{
    int i = tile_pos_1 / size_;
    int j = tile_pos_1 % size_;

    int m = tile_pos_2 / size_;
    int n = tile_pos_2 % size_;

    return (i==m && (j==n+1 || j==n-1)) || (j==n && (i==m+1 || i==m-1));
}

////////////////////////////////////////////////////////////////////////////////

bool map::isAdjacentToAnyInVector(const uint tile_pos, const std::vector<int> v, const int tile_pos_exception) const
{
    for (int i : v)
        if (i>=0 && i!=tile_pos_exception && isAdjacent(i, tile_pos))
            return true;

    return false;
}

////////////////////////////////////////////////////////////////////////////////
