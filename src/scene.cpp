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


    std::vector<ALLEGRO_VERTEX> map_points = tile_map_.draw(cx, cy, screen_w_>screen_h_ ? screen_h_ : screen_w_, screen_w_, 0, screen_h_, 0);

    al_clear_to_color(BACKGROUND_COLOR);
    al_lock_bitmap(al_get_target_bitmap(), ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE );

    al_draw_prim(map_points.data(), nullptr, nullptr, 0, map_points.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

    al_unlock_bitmap(al_get_target_bitmap());
}

void scene::moveX(const double x)
{
    inc_x_ += x;
}

void scene::moveY(const double y)
{
    inc_y_ += y;
}
