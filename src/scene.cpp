#include "../include/scene.hpp"

scene::scene(const uint screen_w, const uint screen_h, const uint map_size, const double tiles_separation, const double map_separation):
    tile_map_(map_size, tiles_separation),
    map_separation_(map_separation),
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
    std::vector<ALLEGRO_VERTEX> vertices;

    double cx = screen_w_/2 + inc_x_;
    double cy = screen_h_/2 + inc_y_;

    tile_map_.appendVertices(vertices, cx, cy, (screen_w_>screen_h_ ? screen_h_ : screen_w_)*(1.0-map_separation_), screen_w_, screen_h_);

    al_clear_to_color(BACKGROUND_COLOR);
    al_lock_bitmap(al_get_target_bitmap(), ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE );

    al_draw_prim(vertices.data(), nullptr, nullptr, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

    al_unlock_bitmap(al_get_target_bitmap());

    std::string stringTriangles("Triangles: "+std::to_string(vertices.size()/3));
    al_draw_text(caviar_font_16, BLACK, 10, 40,ALLEGRO_ALIGN_LEFT, stringTriangles.c_str());
}

void scene::moveX(const double x)
{
    inc_x_ += x;
}

void scene::moveY(const double y)
{
    inc_y_ += y;
}
