#include "../include/scene.hpp"

////////////////////////////////////////////////////////////////////////////////

scene::scene(const double screen_w, const double screen_h, const double map_separation):
    tile_map_(),
    map_separation_(map_separation),
    screen_w_(screen_w),
    screen_h_(screen_h),
    show_menu_(false),
    isplaying_(false),
    istracking_(false),
    esc_was_pressed_(false),

    restart_(restart_image),
    play_(play_disabled_image),
    random_(random_image),
    step_(step_image),
    tracking_(tracking_image),

    quit_("QUIT", al_map_rgb(0,0,0), ubuntu_mono_font_40, 0.2),

    algorithm_({"AAA", "BBBB", "CCCC"}, "Algorithm", ubuntu_mono_font_40, al_map_rgb(0,0,0)),

    width_( "Grid width ", ubuntu_mono_font_40, al_map_rgb(0,0,0), 1, 250, STARTING_SIZE_W),
    height_("Grid height", ubuntu_mono_font_40, al_map_rgb(0,0,0), 1, 250, STARTING_SIZE_H),

    speed_(scroll::VERTICAL),
    obstacles_(scroll::HORIZONTAL, 0.2)
{
    resize(screen_w_, screen_h_);
    tile_map_.rebuild(width_.getValue(), height_.getValue(), obstacles_.getValue());
}

////////////////////////////////////////////////////////////////////////////////

scene::~scene()
{}

////////////////////////////////////////////////////////////////////////////////

void scene::draw()
{
    // CLEAR
    al_clear_to_color(BACKGROUND_COLOR);

    // MENU
    if (show_menu_)
        drawMenu();
    else
        drawSim();
}

////////////////////////////////////////////////////////////////////////////////

void scene::drawSim()
{
    tile_map_.draw();
    al_draw_filled_rectangle(screen_w_-60, 0, screen_w_, screen_h_, PURE_WHITE);

    tracking_.draw();
    restart_.draw();
    step_.draw();
    play_.draw();
    random_.draw();
    speed_.draw();

    // TEXT & DEBUG
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

    if (show_menu_)
    {
        obstacles_.update();
        quit_.update();
        algorithm_.update();
        width_.update();
        height_.update();

        if (quit_.mouseClicked()) quit = true;
    }
    else
    {
        restart_.update();
        play_.update();
        random_.update();
        speed_.update();
        tracking_.update();
        step_.update();
        tile_map_.update();

        double speed = speed_.getValue();

        if (random_.mouseClicked()  ) tile_map_.rebuild(width_.getValue(), height_.getValue(), obstacles_.getValue());
        if (play_.mouseClicked()    ) isplaying_  = !isplaying_;
        if (tracking_.mouseClicked()) istracking_ = !istracking_;
        if (speed < 0.001           ) isplaying_  = false;

        tracking_.setImg(istracking_   ? tracking_image : tracking_disabled_image);
        step_.setImg(speed < 0.001 ? step_image : step_disabled_image);

        if (speed > 0.001)
            play_.setImg(isplaying_ ? pause_image : play_image);
        else
            play_.setImg(play_disabled_image);
    }

    // ESC KEY
    if (keysPress[ALLEGRO_KEY_ESCAPE])
        esc_was_pressed_ = true;
    else if (esc_was_pressed_)
    {
        show_menu_ = !show_menu_;
        esc_was_pressed_ = false;
    }

    if (mouse.shouldBeHand())
        mouse.setCursor(ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
    else
        mouse.setCursor(ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
}

////////////////////////////////////////////////////////////////////////////////

void scene::resize(const double w, const double h)
{
    screen_w_ = w;
    screen_h_ = h;

    tile_map_.moveTo(
        (screen_w_-60)/2.0,
        screen_h_/2.0,
        (screen_w_-60),
        screen_h_
    );

    width_.resize(150, 130);
    height_.resize(150, 220);
    algorithm_.resize(150, 310);

    obstacles_.moveTo(150, 400, screen_w_-300, 5);
    quit_.resize(screen_w_-120, screen_h_-70, 100, 50);
    speed_.moveTo(screen_w_-30, 50, 5, screen_h_-220);
    tracking_.resize(screen_w_-46, 10, 40, 40);
    step_.resize(screen_w_-45, screen_h_-160, 40, 40);
    play_.resize(screen_w_-45, screen_h_-120, 40, 40);
    restart_.resize(screen_w_-45, screen_h_-80 , 40, 40);
    random_.resize( screen_w_-45, screen_h_-40 , 40, 40);
}

////////////////////////////////////////////////////////////////////////////////
