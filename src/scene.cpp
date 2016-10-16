#include "../include/scene.hpp"

////////////////////////////////////////////////////////////////////////////////

scene::scene(const double screen_w, const double screen_h, const uint map_size, const double tiles_separation, const double map_separation):
    tile_map_(map_size, tiles_separation),
    map_separation_(map_separation),
    screen_w_(screen_w),
    screen_h_(screen_h),
    map_size_(map_size),
    inc_x_(0),
    inc_y_(0),
    zoom_(1),
    last_mouse_z_(0),
    show_menu_(false),
    isplaying_(false),
    istracking_(false),
    esc_was_pressed_(false),

    restart_("images/restart.png"),
    play_("images/play_disabled.png"),
    random_("images/random.png"),
    step_("images/step.png"),
    tracking_("images/tracking_disabled.png"),

    quit_("QUIT", default_animation_time_),

    algorithm_("Algorithm  ", {"AAA", "BBBB", "CCCC"}, "images/larrow.png"),

    width_("Grid width ", "images/larrow.png", 1, 100),
    height_("Grid height", "images/larrow.png", 1, 100),

    speed_(scroll::VERTICAL),
    obstacles_(scroll::HORIZONTAL)
{
    resize(screen_w_, screen_h_);
}

////////////////////////////////////////////////////////////////////////////////

scene::~scene()
{}

////////////////////////////////////////////////////////////////////////////////

void scene::generate()
{
    tile_map_.generate();
}

////////////////////////////////////////////////////////////////////////////////

void scene::draw()
{
    std::vector<ALLEGRO_VERTEX> vertices;

    double draw_w = screen_w_-60;
    double cx =    draw_w/2.0 + inc_x_;
    double cy = screen_h_/2.0 + inc_y_;
    double sq_size = (draw_w > screen_h_ ? screen_h_ : draw_w)*zoom_*(1-map_separation_);

    if (!show_menu_)
        tile_map_.appendVertices(vertices, cx, cy, sq_size, draw_w, screen_h_);

    // CLEAR
    al_clear_to_color(BACKGROUND_COLOR);

    // LOCK
    al_lock_bitmap(al_get_target_bitmap(), ALLEGRO_PIXEL_FORMAT_ANY, 0);

    // DRAW
    if (!show_menu_)
    {
        al_draw_prim(vertices.data(), nullptr, nullptr, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
        al_draw_filled_rectangle(screen_w_-60, 0, screen_w_, screen_h_, PURE_WHITE);
    }

    // UNLOCK
    al_unlock_bitmap(al_get_target_bitmap());

    // MENU
    if (show_menu_)
        drawMenu();
    else
        drawSimMenu(vertices.size()/3);

}

////////////////////////////////////////////////////////////////////////////////

#include <iostream>
void scene::drawSimMenu(const uint triangles)
{
    tracking_.draw();
    restart_.draw();
    step_.draw();
    play_.draw();
    random_.draw();
    speed_.draw();

    if (restart_.mouseOver() || play_.mouseOver() || random_.mouseOver() || step_.mouseOver() || tracking_.mouseOver() )
        mouse.setCursor(ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
    else
        mouse.setCursor(ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

    // TEXT & DEBUG
    al_draw_text(caviar_font_16, BLACK, 100, 10,ALLEGRO_ALIGN_LEFT, ("Triangles: "+std::to_string(triangles)).c_str());
    displayFPS(caviar_font_16);
}

////////////////////////////////////////////////////////////////////////////////

void scene::drawMenu()
{
    obstacles_.draw();
    quit_.draw();
    algorithm_.draw();
    width_.draw();
    height_.draw();

    if (quit_.mouseOver() || algorithm_.mouseOverArrow() || width_.mouseOverArrow() || height_.mouseOverArrow())
        mouse.setCursor(ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
    else
        mouse.setCursor(ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

    // TEXT & DEBG
    al_draw_text(caviar_font_16, BLACK, 150, 420,ALLEGRO_ALIGN_LEFT, (std::to_string(int(obstacles_.getValue()*100))+"% Obstacles").c_str());
}

////////////////////////////////////////////////////////////////////////////////

void scene::update()
{
    if (show_menu_)
    {
        obstacles_.update();
        quit_.update();
        algorithm_.update();
        width_.update();
        height_.update();

        if (quit_.wasPressed()) quit = true;
    }
    else
    {
        restart_.update();
        play_.update();
        random_.update();
        speed_.update();
        tracking_.update();
        step_.update();

        double speed = speed_.getValue();

        if (play_.wasPressed()    ) isplaying_  = !isplaying_;
        if (tracking_.wasPressed()) istracking_ = !istracking_;
        if (speed < 0.001         ) isplaying_  = false;

        tracking_.setImage(istracking_   ? "images/tracking.png" : "images/tracking_disabled.png");
        step_.setImage(speed < 0.001 ? "images/step.png" : "images/step_disabled.png");

        if (speed > 0.001)
            play_.setImage(isplaying_ ? "images/pause.png" : "images/play.png");
        else
            play_.setImage("images/play_disabled.png");
    }

    // ESC KEY
    if (keysPress[ALLEGRO_KEY_ESCAPE])
        esc_was_pressed_ = true;
    else if (esc_was_pressed_)
    {
        show_menu_ = !show_menu_;
        esc_was_pressed_ = false;
    }

    // ZOOM
    zoom_ += (mouse.getZ() - last_mouse_z_)*0.1;
    zoom_ = zoom_ < 0.1 ? 0.1 : zoom_;

    last_mouse_z_ = mouse.getZ();
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

    width_.moveTo(150, 130);
    height_.moveTo(150, 220);
    algorithm_.moveTo(150, 310);

    obstacles_.moveTo(150, 400, screen_w_-300, 5);
    quit_.moveTo(screen_w_-120, screen_h_-70, 100, 50);
    speed_.moveTo(screen_w_-30, 50, 5, screen_h_-220);
    tracking_.moveTo(screen_w_-46, 10, 40, 40);
    step_.moveTo(screen_w_-45, screen_h_-160, 40, 40);
    play_.moveTo(screen_w_-45, screen_h_-120, 40, 40);
    restart_.moveTo(screen_w_-45, screen_h_-80 , 40, 40);
    random_.moveTo( screen_w_-45, screen_h_-40 , 40, 40);
}

////////////////////////////////////////////////////////////////////////////////
