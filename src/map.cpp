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

    std::vector<point> tilePoints(4);

    // Tiles are stored from left to right, bottom to top. Starting from the middle left vertex.
    for (uint i=0; i<size; ++i)
        for (uint j=0; j<size; ++j)
        {
            double x = vertices_[0].x + i*delta + j*delta;
            double y = vertices_[0].y + i*delta - j*delta;

            tilePoints[0].set(x + delta*(BORDER  ), y                   );
            tilePoints[1].set(x + delta           , y + delta*(BORDER-1));
            tilePoints[2].set(x + delta*(2-BORDER), y                   );
            tilePoints[3].set(x + delta           , y + delta*(1-BORDER));

            bool border = i==0 || j==0 || (i+1)>=size_ || (j+1)>=size_;

            tiles_.emplace_back(tilePoints, border);
        }

    int pos=0;
    for (int i=0; i<int(size_); ++i)
        for (int j=0; j<int(size_); ++j, ++pos)
        {
            int ii, jj;

            // Adjacents
            ii = i  ; jj = j+1; tiles_[pos].storeFriend((ii<int(size_) && jj<int(size_) && jj>=0 && ii>=0) ? &tiles_[ii*size_+jj] : nullptr, dir::UP_RIGHT);
            ii = i  ; jj = j-1; tiles_[pos].storeFriend((ii<int(size_) && jj<int(size_) && jj>=0 && ii>=0) ? &tiles_[ii*size_+jj] : nullptr, dir::DOWN_LEFT);
            ii = i+1; jj = j  ; tiles_[pos].storeFriend((ii<int(size_) && jj<int(size_) && jj>=0 && ii>=0) ? &tiles_[ii*size_+jj] : nullptr, dir::DOWN_RIGHT);
            ii = i-1; jj = j  ; tiles_[pos].storeFriend((ii<int(size_) && jj<int(size_) && jj>=0 && ii>=0) ? &tiles_[ii*size_+jj] : nullptr, dir::UP_LEFT);

            // Neighbors
            ii = i+1; jj = j+1; tiles_[pos].storeFriend((ii<int(size_) && jj<int(size_) && jj>=0 && ii>=0) ? &tiles_[ii*size_+jj] : nullptr, dir::RIGHT);
            ii = i+1; jj = j-1; tiles_[pos].storeFriend((ii<int(size_) && jj<int(size_) && jj>=0 && ii>=0) ? &tiles_[ii*size_+jj] : nullptr, dir::DOWN);
            ii = i-1; jj = j+1; tiles_[pos].storeFriend((ii<int(size_) && jj<int(size_) && jj>=0 && ii>=0) ? &tiles_[ii*size_+jj] : nullptr, dir::UP);
            ii = i-1; jj = j-1; tiles_[pos].storeFriend((ii<int(size_) && jj<int(size_) && jj>=0 && ii>=0) ? &tiles_[ii*size_+jj] : nullptr, dir::LEFT);
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

void map::generateScenario(const uint rivers, const uint min_size_river, const bool accumulative_rivers)
{
    std::uniform_int_distribution<int> random_switch(0,3);
    std::uniform_int_distribution<int> random_tile(0,size_-1);
    uint rivers_made = 0;
    uint sentinel = 0;

    while (rivers_made < rivers)
    {
        // Check for infinite loop
        if (++sentinel==SENTINEL_MAX) return;

        // Slect a random direction
        dir river_direction;
        switch (random_switch(generator_))
        {
            case 0: river_direction = dir::UP;    break;
            case 1: river_direction = dir::DOWN;  break;
            case 2: river_direction = dir::LEFT;  break;
            case 3: river_direction = dir::RIGHT; break;
            default: break;
        }

        // Select a random border tile
        uint start;
        switch (random_switch(generator_))
        {
            case 0: start = random_tile(generator_)*size_ + size_-1; break;
            case 1: start = random_tile(generator_)*size_; break;
            case 2: start = (size_-1)*size_ + random_tile(generator_); break;
            case 3: start = random_tile(generator_); break;
        }

        // Generate the river
        if (generateRiver(start, river_direction, min_size_river, accumulative_rivers))
            rivers_made++;
    }
}

////////////////////////////////////////////////////////////////////////////////

bool map::generateRiver(const uint start, const dir direction, const uint min_size, const bool accumulative)
{
    std::normal_distribution<double> normal(0.0,0.3);
    std::vector<tile*> river;

    tile* target=nullptr;
    tile* current= &tiles_[start];
    river.push_back(current);

    // Convert the direction the river is going to an angle
    double target_angle;
    switch (direction)
    {
        case dir::UP:    target_angle =  90.0; break;
        case dir::DOWN:  target_angle = 270.0; break;
        case dir::LEFT:  target_angle = 180.0; break;
        case dir::RIGHT: target_angle =   0.0; break;
        default: return false;
    }

    // Expand the river while it is too small or there is still a valid target
    for (uint river_size = 0; river_size < min_size || target; ++river_size)
    {
        uint sentinel = 0;
        do
        {
            // Check for infinite loop
            if (++sentinel==SENTINEL_MAX) return false;

            // Generate a new angle for the river with a maximum deviation of +-135 degrees
            double deviation = target_angle + normal(generator_)*135.0;
            target_angle = accumulative ? deviation : target_angle;
            while (deviation > 360) deviation -= 360;

            // The new direction the river will be facing
            dir target_direction;
            if (deviation < 180) target_direction = deviation< 90 ? dir::UP_RIGHT  : dir::UP_LEFT;
            else                 target_direction = deviation<270 ? dir::DOWN_LEFT : dir::DOWN_RIGHT;

            // Get the tile in that direction
            target = current->getFriend(target_direction);
                                                                                // CALCULATE A NEW TARGET TILE WHILE:
        } while ((river_size < min_size && (!target || target->isBorder()))  ||  // River is too small and target was not found or is a border
                 isAdjacentToAnyInVector(target, river, current));              // Target is adjacent to other river tile (Except the current one)

        // Add the target tile to the river tiles
        if (target) river.push_back(target);
        current = target;
    }

    // Set all river tiles
    for (tile* i : river)
        i->setColor(RIVER_TILE_COLOR); // TODO remove if

    return true;
}

////////////////////////////////////////////////////////////////////////////////

void map::neutralizeAllTiles()
{
    for (tile &i : tiles_) i.setColor(NEUTRAL_TILE_COLOR);
}

////////////////////////////////////////////////////////////////////////////////

bool map::isAdjacentToAnyInVector(const tile* test, const std::vector<tile*>& v, const tile* test_exception) const
{
    for (const tile* i : v)
        if (i!=test_exception && test && test->isAdjacentTo(i)) // The  tile is adjacent to the target tile and the (vector) tile is not an exception
            return true;

    return false;
}

////////////////////////////////////////////////////////////////////////////////
