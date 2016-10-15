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

    static bool playing_ = false;

    static button restart_button(   "Restart"  , 0.15);
    static button play_pause_button("Play"     , 0.15);
    static button randomize_button( "Randomize", 0.15);
    static button step_button(      "Step"     , 0);
    static button real_button(      "Real", 0);

    static scrollbar speed_scrollbar;

    restart_button.moveTo(   0               , screen_h_-70.0, screen_w_/3.0, 80.0         );
    play_pause_button.moveTo(screen_w_*0.3333, screen_h_-70.0, screen_w_/3.0, 80.0         );
    randomize_button.moveTo( screen_w_*0.6666, screen_h_-70.0, screen_w_/3.0, 80.0         );
    speed_scrollbar.moveTo(  screen_w_-30    , 50            , 5            , screen_h_-150);
    step_button.moveTo(      screen_w_-50    , 10            , 40           , 40           );
    real_button.moveTo(      screen_w_-50    , 10            , 40           , 40           );

    restart_button.update();
    play_pause_button.update();
    randomize_button.update();
    speed_scrollbar.update();
    step_button.update();

    double cx = screen_w_/2.0 + inc_x_;
    double cy = screen_h_/2.0 + inc_y_;

    static double zoom = 1; // TODO mouse inside
    zoom = mouse.getZ()*0.1 + 1;

    // GET VERTICES
    tile_map_.appendVertices(vertices, cx, cy, screen_h_*zoom, screen_w_-50, screen_h_-50);

    // CLEAR & LOCK
    al_clear_to_color(BACKGROUND_COLOR);
    al_lock_bitmap(al_get_target_bitmap(), ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE );

    // DRAW
    al_draw_prim(vertices.data(), nullptr, nullptr, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
    al_draw_filled_rectangle(0, 0, screen_w_, 40, BACKGROUND_COLOR);
    al_draw_filled_rectangle(screen_w_-60, 0, screen_w_, screen_h_, BACKGROUND_COLOR);
    al_draw_filled_rectangle(10, 0, 0, screen_h_, BACKGROUND_COLOR);
    al_draw_filled_rectangle(0, screen_h_-60, screen_w_, screen_h_, BACKGROUND_COLOR);

    // UNLOCK
    al_unlock_bitmap(al_get_target_bitmap());

    double speed = speed_scrollbar.getValue();

    if (speed > 0.999)
        real_button.draw();
    if (speed < 0.001)
        step_button.draw();

    restart_button.draw();
    play_pause_button.draw();
    randomize_button.draw();
    speed_scrollbar.draw();

    if (play_pause_button.wasPressed())
    {
        playing_ = !playing_;
        play_pause_button.setLabel(playing_ ? "Play" : "Pause");
    }

    if (restart_button.mouseOver()    ||
        play_pause_button.mouseOver() ||
        randomize_button.mouseOver()  ||
        (step_button.mouseOver() && speed<0.001) )

        mouse.setCursor(ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
    else
        mouse.setCursor(ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

    // TEXT & DEBG
    al_draw_text(caviar_font_16, BLACK, 100, 10,ALLEGRO_ALIGN_LEFT, ("Triangles: "+std::to_string(vertices.size()/3)).c_str());
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

void scene::resize(const double w, const double h)
{
    screen_w_ = w;
    screen_h_ = h;
}

////////////////////////////////////////////////////////////////////////////////
