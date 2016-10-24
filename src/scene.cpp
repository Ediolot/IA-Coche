#include "../include/scene.hpp"

////////////////////////////////////////////////////////////////////////////////

scene::scene(const double screen_w, const double screen_h, const double tiles_separation, const double map_separation):
    tile_map_(20, 20, 0.2, tiles_separation),
    map_separation_(map_separation),
    screen_w_(screen_w),
    screen_h_(screen_h),
    inc_x_(0),
    inc_y_(0),
    zoom_(1),
    last_mouse_z_(0),
    show_menu_(false),
    isplaying_(false),
    istracking_(false),
    esc_was_pressed_(false),

    restart_(restart_image),
    play_(play_disabled_image),
    random_(random_image),
    step_(step_image),
    tracking_(tracking_image),

    quit_("QUIT", ubuntu_mono_font_40, &BLACK, default_animation_time_),

    algorithm_({"AAA", "BBBB", "CCCC"}, "Algorithm", ubuntu_mono_font_40, &BLACK),

    width_("Grid width ", ubuntu_mono_font_40, &BLACK, 1, 100, 20),
    height_("Grid height", ubuntu_mono_font_40, &BLACK, 1, 100, 20),

    speed_(scroll::VERTICAL),
    obstacles_(scroll::HORIZONTAL, 0.2)
{
    resize(screen_w_, screen_h_);
}

///////////////////////////////////////////////////////////////////////////////

scene::~scene()
{}

////////////////////////////////////////////////////////////////////////////////

void scene::draw()
{
    std::vector<ALLEGRO_VERTEX> vertices_text1, vertices_text2;

    double draw_w = screen_w_-60;
    double cx =    draw_w/2.0 + inc_x_;
    double cy = screen_h_/2.0 + inc_y_;
    double h_size = screen_h_/tile_map_.getNRows();
    double w_size = screen_w_/tile_map_.getNCols();
    double sq_size = (w_size*tile_map_.getNRows() > screen_h_ ? h_size : w_size)*zoom_*(1-map_separation_);

    if (!show_menu_)
        tile_map_.appendVertices(vertices_text1, vertices_text2, cx, cy, sq_size, draw_w, screen_h_);

    // CLEAR
    al_clear_to_color(BACKGROUND_COLOR);

    // LOCK
    al_lock_bitmap(al_get_target_bitmap(), ALLEGRO_PIXEL_FORMAT_ANY, 0);

    // DRAW
    if (!show_menu_)
    {
        al_draw_prim(vertices_text1.data(), nullptr, floor_image, 0, vertices_text1.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
        al_draw_prim(vertices_text2.data(), nullptr, wall_image, 0, vertices_text2.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
        al_draw_filled_rectangle(screen_w_-60, 0, screen_w_, screen_h_, PURE_WHITE);
    }

    // UNLOCK
    al_unlock_bitmap(al_get_target_bitmap());

    // MENU
    if (show_menu_)
        drawMenu();
    else
        drawSimMenu((vertices_text1.size()+vertices_text2.size())/3);

}

////////////////////////////////////////////////////////////////////////////////

void scene::drawSimMenu(const uint triangles)
{
    tracking_.draw();
    restart_.draw();
    step_.draw();
    play_.draw();
    random_.draw();
    speed_.draw();

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

    // TEXT & DEBG
    al_draw_text(caviar_font_16, BLACK, 150, 420, ALLEGRO_ALIGN_LEFT, (std::to_string(int(obstacles_.getValue()*100))+"% Obstacles").c_str());
}

////////////////////////////////////////////////////////////////////////////////

void scene::update()
{
    mouse.setShouldBeHand(false);

    obstacles_.update();
    quit_.update();
    algorithm_.update();
    width_.update();
    height_.update();
    restart_.update();
    play_.update();
    random_.update();
    speed_.update();
    tracking_.update();
    step_.update();

    double speed = speed_.getValue();

    if (speed < 0.001 )
    {
        isplaying_ = false;
        play_.setImg(play_disabled_image);
    }
    else
    {
        if (play_.mouseClicked())
            isplaying_ = !isplaying_;

        play_.setImg(isplaying_ ? pause_image : play_image);
    }

    if (quit_.mouseClicked())
        quit=true;

    if (tracking_.mouseClicked())
        istracking_ = !istracking_;

    if (random_.mouseClicked())
    {
        inc_x_ = inc_y_ = 0;
        zoom_ = 1;
        tile_map_.rebuild(width_.getValue(), height_.getValue());
        tile_map_.generate(obstacles_.getValue());
    }

    tracking_.setImg(istracking_   ? tracking_image : tracking_disabled_image);
    step_.setImg(speed < 0.001 ? step_image : step_disabled_image);

    // Clicked on map
    tile_map_.checkClick();

    // ZOOM
    if (mouse.insideBox(0,0,screen_w_-60,screen_h_))
        zoom_ += (mouse.getZ() - last_mouse_z_)*0.1;
    zoom_ = zoom_ < 0.1 ? 0.1 : zoom_;

    // ESC KEY
    if (keysPress[ALLEGRO_KEY_ESCAPE])
        esc_was_pressed_ = true;
    else if (esc_was_pressed_)
    {
        if (show_menu_)
        {
            show_menu_ = false;
            obstacles_.hide();
            quit_.hide();
            algorithm_.hide();
            width_.hide();
            height_.hide();
            tracking_.show();
            restart_.show();
            step_.show();
            play_.show();
            random_.show();
            speed_.show();
        }
        else
        {
            show_menu_ = true;
            obstacles_.show();
            quit_.show();
            algorithm_.show();
            width_.show();
            height_.show();
            tracking_.hide();
            restart_.hide();
            step_.hide();
            play_.hide();
            random_.hide();
            speed_.hide();
        }

        esc_was_pressed_ = false;
    }

    last_mouse_z_ = mouse.getZ();
    mouse.setCursor(mouse.shouldBeHand() ? ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK : ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
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

    width_.resize(150, 130);
    height_.resize(150, 220);
    algorithm_.resize(150, 310);

    obstacles_.moveTo(150, 400, screen_w_-300, 5);
    speed_.moveTo(screen_w_-30, 50, 5, screen_h_-220);
    quit_.resize(screen_w_-120, screen_h_-70, 100, 50);
    tracking_.resize(screen_w_-46, 10, 40, 40);
    step_.resize(screen_w_-45, screen_h_-160, 40, 40);
    play_.resize(screen_w_-45, screen_h_-120, 40, 40);
    restart_.resize(screen_w_-45, screen_h_-80 , 40, 40);
    random_.resize( screen_w_-45, screen_h_-40 , 40, 40);
}

////////////////////////////////////////////////////////////////////////////////
