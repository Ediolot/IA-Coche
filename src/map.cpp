#include "../include/map.hpp"

////////////////////////////////////////////////////////////////////////////////

map::map(const uint size, const uint seed):
    generator_(seed ? seed : std::time(nullptr)),
    tiles_(),
    size_(size)
{
    for (uint i=0; i<size_; ++i)
        for (uint j=0; j<size_; ++j)
            tiles_.emplace_back(i==0 || j==0 || i==(size_-1) || j==(size_-1));

    for (uint i=0; i<tiles_.size(); ++i)
    {
        tiles_[i].addFriend( accessTile(i / size_, i % size_, dir::UP)        , dir::UP       );
        tiles_[i].addFriend( accessTile(i / size_, i % size_, dir::DOWN)      , dir::DOWN     );
        tiles_[i].addFriend( accessTile(i / size_, i % size_, dir::LEFT)      , dir::LEFT     );
        tiles_[i].addFriend( accessTile(i / size_, i % size_, dir::RIGHT)     , dir::RIGHT    );

        tiles_[i].addFriend( accessTile(i / size_, i % size_, dir::UP_RIGHT)  , dir::UP_RIGHT );
        tiles_[i].addFriend( accessTile(i / size_, i % size_, dir::UP_LEFT)   , dir::UP_LEFT  );
        tiles_[i].addFriend( accessTile(i / size_, i % size_, dir::DOWN_LEFT) , dir::DOWN_LEFT);
        tiles_[i].addFriend( accessTile(i / size_, i % size_, dir::DOWN_RIGHT), dir::DOWN_RIGHT);
    }
}

////////////////////////////////////////////////////////////////////////////////

map::~map()
{}

////////////////////////////////////////////////////////////////////////////////

void map::draw(const double cx, const double cy, const double width, const double border) const
{
    const double delta       = width / size_;
    const double delta_2     = delta/2;
    const point  left_corner = {cx - (width/2) + delta, cy};

    uint pos=0;
    for (uint i=0; i<size_; ++i)
        for (uint j=0; j<size_; ++j, ++pos)
            tiles_[pos].draw(left_corner.x + delta_2*(i+j), left_corner.y + delta_2*(double(j)-double(i)), delta, border);
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
    double target_angle = directionToDegrees(direction);

    river.push_back(current);

    // Expand the river while it is too small or there is still a valid target
    for (uint river_size = 0; river_size < min_size || target; ++river_size)
    {
        uint sentinel = 0;
        do
        {
            // Check for infinite loop
            if (++sentinel==SENTINEL_MAX) return false;

            // Generate a new angle for the river with a maximum deviation of +-135 degrees
            double diverted_angle = normalAngle(target_angle + normal(generator_)*135.0);
            if (accumulative) target_angle = diverted_angle;

            // The new direction the river will be facing
            dir target_direction;
            if (diverted_angle < 180) target_direction = diverted_angle< 90 ? dir::UP_RIGHT  : dir::UP_LEFT;
            else                      target_direction = diverted_angle<270 ? dir::DOWN_LEFT : dir::DOWN_RIGHT;

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
