#include "map.hpp"

map::map(const uint size, const double screenWidth, const double screenHeight, const double percent):
    tiles_(),
    vertices_(),
    size_(size)
{

    double width  = screenWidth * percent;
    double height = screenHeight * percent;
    double square_side = width < height ? width : height;
    double side = 0.7071 * square_side;

    vertices_[0].set((screenWidth - square_side) / 2, screenHeight / 2);
    vertices_[2].set((screenWidth + square_side) / 2, screenHeight / 2);

    vertices_[1].set(screenWidth / 2, (screenHeight - square_side) / 2);
    vertices_[3].set(screenWidth / 2, (screenHeight + square_side) / 2);

    // Create tiles:

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

            tiles_.emplace_back(tilePoints);
        }
    }
}

map::~map()
{}

void map::draw() const
{
    for (auto &i : tiles_) i.draw();
}
