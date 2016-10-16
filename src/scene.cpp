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

void scene::draw() const
{
    std::vector<ALLEGRO_VERTEX> vertices;

    static bool show_menu_ = false;
    static bool playing_   = false;
    static bool tracking_  = false;

    static button_image restart_button("images/restart.png");
    static button_image play_pause_button("images/play_disabled.png");
    static button_image randomize_button("images/random.png");
    static button_image step_button("images/step.png");
    static button_image tracking_button("images/tracking_disabled.png");
    static button       quit_button("QUIT", 0.2);

    static scrollbar speed_scrollbar(scroll::VERTICAL);
    static scrollbar obstacles_scrollbar(scroll::HORIZONTAL);

    static bool esc_was_pressed = false;
    if (keysPress[ALLEGRO_KEY_ESCAPE])
        esc_was_pressed = true;
    if (!keysPress[ALLEGRO_KEY_ESCAPE] && esc_was_pressed)
    {
        show_menu_ = !show_menu_;
        esc_was_pressed = false;
    }

    double cx = screen_w_/2.0 + inc_x_;
    double cy = screen_h_/2.0 + inc_y_;

    static double zoom = 1; // TODO mouse inside
    zoom = mouse.getZ()*0.1 + 1;

    // GET VERTICES
    if (!show_menu_)
        tile_map_.appendVertices(vertices, cx, cy, screen_h_*zoom, screen_w_-50, screen_h_);

    // CLEAR
    al_clear_to_color(BACKGROUND_COLOR);

    // LOCK
    //al_lock_bitmap(al_get_target_bitmap(), ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE );

    // DRAW
    if (!show_menu_)
    {
        al_draw_prim(vertices.data(), nullptr, nullptr, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
        al_draw_filled_rectangle(screen_w_-60, 0, screen_w_, screen_h_, PURE_WHITE);
    }

    // UNLOCK
    //al_unlock_bitmap(al_get_target_bitmap());

    if (!show_menu_)
    {
        speed_scrollbar.moveTo(  screen_w_-30, 50, 5, screen_h_-220);

        tracking_button.moveTo(  screen_w_-46, 10           , 40, 40);
        step_button.moveTo(      screen_w_-45, screen_h_-160, 40, 40);
        play_pause_button.moveTo(screen_w_-45, screen_h_-120, 40, 40);
        restart_button.moveTo(   screen_w_-45, screen_h_-80 , 40, 40);
        randomize_button.moveTo( screen_w_-45, screen_h_-40 , 40, 40);

        restart_button.update();
        play_pause_button.update();
        randomize_button.update();
        speed_scrollbar.update();
        step_button.update();
        tracking_button.update();
        double speed = speed_scrollbar.getValue();

        if (play_pause_button.wasPressed())
            playing_ = !playing_;

        if (tracking_button.wasPressed())
            tracking_ = !tracking_;

        if (speed < 0.001)
            playing_ = false;

        tracking_button.setImage(tracking_ ? "images/tracking.png" : "images/tracking_disabled.png");
        step_button.setImage(speed < 0.001 ? "images/step.png" : "images/step_disabled.png");
        if (speed > 0.001)
            play_pause_button.setImage(playing_ ? "images/pause.png" : "images/play.png");
        else
            play_pause_button.setImage("images/play_disabled.png");

        tracking_button.draw();
        restart_button.draw();
        step_button.draw();
        play_pause_button.draw();
        randomize_button.draw();
        speed_scrollbar.draw();

        if (restart_button.mouseOver()    ||
            play_pause_button.mouseOver() ||
            randomize_button.mouseOver()  ||
            step_button.mouseOver()       ||
            tracking_button.mouseOver() )

            mouse.setCursor(ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
        else
            mouse.setCursor(ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
    }
    else
    {
        obstacles_scrollbar.moveTo(150, 300, screen_w_-300, 5);
        quit_button.moveTo(screen_w_-120, screen_h_-70, 100, 50);
        obstacles_scrollbar.update();
        quit_button.update();
        obstacles_scrollbar.draw();
        quit_button.draw();

        al_draw_text(caviar_font_16, BLACK, 150, 320,ALLEGRO_ALIGN_LEFT, (std::to_string(int(obstacles_scrollbar.getValue()*100))+"% Obstacles").c_str());

        if (quit_button.mouseOver())
            mouse.setCursor(ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
        else
            mouse.setCursor(ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

        if (quit_button.wasPressed())
            quit = true;
    }

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
