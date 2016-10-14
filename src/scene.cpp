#include "../include/scene.hpp"

scene::scene(const uint screen_w, const uint screen_h, const uint map_size, const double map_separation):
    tile_map_(map_size, map_separation),
    screen_w_(screen_w),
    screen_h_(screen_h),
    map_size_(map_size),
    inc_x_(0),
    inc_y_(0)
{}

scene::~scene()
{}

void scene::generate(const uint rivers, const uint min_size_river, const bool accumulative_rivers)
{
    tile_map_.generateScenario(rivers,min_size_river,accumulative_rivers);
}

void scene::draw() const
{
    triangles_global = 0;

    double cx = screen_w_/2 + inc_x_;
    double cy = screen_h_/2 + inc_y_;

    al_clear_to_color(BACKGROUND_COLOR);
    tile_map_.draw(cx, cy, screen_w_>screen_h_ ? screen_h_ : screen_w_, screen_w_, 0, screen_h_, 0);
}

void scene::moveX(const double x)
{
    inc_x_ += x;
}

void scene::moveY(const double y)
{
    inc_y_ += y;
}
