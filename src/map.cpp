#include "../include/map.hpp"

////////////////////////////////////////////////////////////////////////////////

map::map(const uint size, const uint seed = 0):
    generator_(seed ? seed : std::time(nullptr)),
    tiles_(size*size),
    size_(size)
{}

////////////////////////////////////////////////////////////////////////////////

map::~map()
{}

////////////////////////////////////////////////////////////////////////////////

void map::draw(const double cx, const double cy, const double width) const
{
    const double delta       = (width/2) / size_;
    const point  left_corner = {cx - (width/2) + delta, cy};

    uint pos=0;
    for (uint i=0; i<size_; ++i)
        for (uint j=0; j<size_; ++j, ++pos)
            tiles_[pos].draw(left_corner.x, left_corner.y, delta);
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
