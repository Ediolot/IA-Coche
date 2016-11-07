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
    obstacles_text_("0% Obstacles", al_map_rgb(0,0,0), caviar_font_16),

    algorithm_({"AAA", "BBBB", "CCCC"}, "Algorithm", ubuntu_mono_font_40, al_map_rgb(0,0,0)),

    width_( "Grid width ", ubuntu_mono_font_40, al_map_rgb(0,0,0), 1, 250, STARTING_SIZE_W),
    height_("Grid height", ubuntu_mono_font_40, al_map_rgb(0,0,0), 1, 250, STARTING_SIZE_H),

    speed_(scrollbar::type::VERTICAL),
    obstacles_(scrollbar::type::HORIZONTAL, 0.2)
{
    resize(screen_w_, screen_h_);
    tile_map_.rebuild(width_.getValue(), height_.getValue(), obstacles_.getValue());
    showMenu(show_menu_);
}

////////////////////////////////////////////////////////////////////////////////

scene::~scene()
{}

////////////////////////////////////////////////////////////////////////////////

void scene::draw()
{
    // CLEAR
    al_clear_to_color(BACKGROUND_COLOR);

    // TEXT & DEBUG
    displayFPS(caviar_font_16);

    if (!show_menu_)
    {
        tile_map_.draw();
        al_draw_filled_rectangle(screen_w_-60, 0, screen_w_, screen_h_, PURE_WHITE);
    }

    obstacles_.draw();
    quit_.draw();
    algorithm_.draw();
    width_.draw();
    height_.draw();
    obstacles_text_.draw();
    tracking_.draw();
    restart_.draw();
    step_.draw();
    play_.draw();
    random_.draw();
    speed_.draw();
}

////////////////////////////////////////////////////////////////////////////////

void scene::showMenu(bool show)
{
    obstacles_.show(show);
    quit_.show(show);
    algorithm_.show(show);
    width_.show(show);
    height_.show(show);
    obstacles_text_.show(show);
    play_.show(!show);
    random_.show(!show);
    speed_.show(!show);
    tracking_.show(!show);
    step_.show(!show);
    tile_map_.show(!show);
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
    tile_map_.update();

    double speed = speed_.getValue();

    if (quit_.mouseClicked()    ) quit = true;
    if (random_.mouseClicked()  ) tile_map_.rebuild(width_.getValue(), height_.getValue(), obstacles_.getValue());
    if (play_.mouseClicked()    ) isplaying_  = !isplaying_;
    if (tracking_.mouseClicked()) istracking_ = !istracking_;
    if (speed < 0.001           ) isplaying_  = false;

    if (isplaying_ || step_.mouseClicked())
        tile_map_.updatePlayer();

    obstacles_text_.setText(std::to_string(int(obstacles_.getValue()*100))+"% Obstacles");
    tracking_.setImg(istracking_   ? tracking_image : tracking_disabled_image);
    step_.setImg(    speed < 0.001 ? step_image     : step_disabled_image);

    if (speed > 0.001)
        play_.setImg(isplaying_ ? pause_image : play_image);
    else
        play_.setImg(play_disabled_image);

    // ESC KEY
    if (keysPress[ALLEGRO_KEY_ESCAPE])
        esc_was_pressed_ = true;
    else if (esc_was_pressed_)
    {
        show_menu_ = !show_menu_;
        showMenu(show_menu_);
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

    tile_map_.resize(
        (screen_w_-60)/2.0,
        screen_h_/2.0,
        (screen_w_-60),
        screen_h_
    );

    width_.resize(150, 130);
    height_.resize(150, 220);
    algorithm_.resize(150, 310);
    obstacles_text_.resize(150, 420);
    obstacles_.resize(150, 400, screen_w_-300, 5);
    quit_.resize(screen_w_-120, screen_h_-70, 100, 50);
    speed_.resize(screen_w_-30, 50, 5, screen_h_-220);
    tracking_.resize(screen_w_-46, 10, 40, 40);
    step_.resize(screen_w_-45, screen_h_-160, 40, 40);
    play_.resize(screen_w_-45, screen_h_-120, 40, 40);
    restart_.resize(screen_w_-45, screen_h_-80 , 40, 40);
    random_.resize( screen_w_-45, screen_h_-40 , 40, 40);
}

////////////////////////////////////////////////////////////////////////////////
