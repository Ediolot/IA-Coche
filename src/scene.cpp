#include "../include/scene.hpp"

////////////////////////////////////////////////////////////////////////////////

scene::scene(const double screen_w, const double screen_h, const uint map_size, const double tiles_separation, const double map_separation):
    tile_map_(map_size, tiles_separation),
    map_separation_(map_separation),
    screen_w_(screen_w),
    screen_h_(screen_h),
    map_size_(map_size),
    inc_x_(0),
    inc_y_(0)
{}

////////////////////////////////////////////////////////////////////////////////

scene::~scene()
{}

////////////////////////////////////////////////////////////////////////////////

void scene::generate(const uint rivers, const uint min_size_river, const bool accumulative_rivers)
{
    tile_map_.generate(rivers,min_size_river,accumulative_rivers);
}

////////////////////////////////////////////////////////////////////////////////
#include <iostream>
void scene::draw() const
{
    std::vector<ALLEGRO_VERTEX> vertices;

    static button restart_button(   "Restart"  , 0.15);
    static button play_pause_button("Play"     , 0.15);
    static button randomize_button( "Randomize", 0.15);
    static button speed_button( "Step", 0.15);
    static scrollbar speed(0.15);

    restart_button.moveTo(                  0, screen_h_-80.0, screen_w_/3.0, 80.0);
    play_pause_button.moveTo(screen_w_*0.3333, screen_h_-80.0, screen_w_/3.0, 80.0);
    randomize_button.moveTo( screen_w_*0.6666, screen_h_-80.0, screen_w_/3.0, 80.0);
    speed.moveTo(screen_w_-30, 50, 5, screen_h_-200);

    restart_button.update();
    play_pause_button.update();
    randomize_button.update();
    speed.update();
    std::cout << "\r" << speed.getValue() << "               ";

    //double cx = screen_w_/2.0 + inc_x_;
    //double cy = screen_h_/2.0 + inc_y_;

    // GET VERTICES
    //tile_map_.appendVertices(vertices, cx, cy, (screen_w_>screen_h_ ? screen_h_ : screen_w_)*(1.0-map_separation_), screen_w_, screen_h_);

    // CLEAR & LOCK
    al_clear_to_color(BACKGROUND_COLOR);
    //al_lock_bitmap(al_get_target_bitmap(), ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE );

    // DRAW
    //al_draw_prim(vertices.data(), nullptr, nullptr, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

    // UNLOCK
    //al_unlock_bitmap(al_get_target_bitmap());

    if (restart_button.wasPressed())
        std::cout << "RESTART" << std::endl;
    if (play_pause_button.wasPressed())
    {
        std::cout << "PLAY" << std::endl;
    }
    if (randomize_button.wasPressed())
        std::cout << "RANDOMIZE" << std::endl;

    restart_button.draw();
    play_pause_button.draw();
    randomize_button.draw();
    speed.draw();

    if (restart_button.mouseOver()    ||
        play_pause_button.mouseOver() ||
        randomize_button.mouseOver() )

        mouse.setCursor(ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
    else
        mouse.setCursor(ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

    // TEXT & DEBG
    al_draw_text(caviar_font_16, BLACK, 10, 40,ALLEGRO_ALIGN_LEFT, ("Triangles: "+std::to_string(vertices.size()/3)).c_str());
    displayFPS(caviar_font_16);
}

////////////////////////////////////////////////////////////////////////////////

void scene::moveX(const double x)
{
    inc_x_ += x;
}

////////////////////////////////////////////////////////////////////////////////

void scene::moveY(const double y)
{
    inc_y_ += y;
}

////////////////////////////////////////////////////////////////////////////////
