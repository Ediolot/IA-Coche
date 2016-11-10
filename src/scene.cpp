#include "../include/scene.hpp"

////////////////////////////////////////////////////////////////////////////////

scene::scene(const double screen_w, const double screen_h, const double map_separation):
    mutex(al_create_mutex()),
    cond(al_create_cond()),
    ready (false),
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

    algorithm_({"A*"}, "Algorithm", ubuntu_mono_font_40, al_map_rgb(0,0,0)),

    width_( "Grid width ", ubuntu_mono_font_40, al_map_rgb(0,0,0), 1, 250, STARTING_SIZE_W),
    height_("Grid height", ubuntu_mono_font_40, al_map_rgb(0,0,0), 1, 250, STARTING_SIZE_H),

<<<<<<< HEAD
    info_("FPS: 0", al_map_rgb(0,0,0), caviar_font_16),
    fps_(0),
    result_(0),
    time_(0),
=======
    fps_label_("FPS: 0", al_map_rgb(0,0,0), caviar_font_16),
    result_(0),
    info_("Buscando camino...", al_map_rgb(0,0,0), caviar_font_16),
    fps_(0),
>>>>>>> e617387924510b31714e3f47995e77005de53387

    speed_(scrollbar::type::VERTICAL),
    obstacles_(scrollbar::type::HORIZONTAL, 0.2)
{
    al_lock_mutex(mutex);
    resize(screen_w_, screen_h_);
    tile_map_.rebuild(width_.getValue(), height_.getValue(), obstacles_.getValue());
    showMenu(show_menu_);
    al_unlock_mutex(mutex);
}

////////////////////////////////////////////////////////////////////////////////

scene::~scene()
{
    al_destroy_mutex(mutex);
    al_destroy_cond(cond);
}

////////////////////////////////////////////////////////////////////////////////

void scene::draw()
{
    // CLEAR
    al_clear_to_color(BACKGROUND_COLOR);

    if (!show_menu_)
    {
        tile_map_.draw();
        al_draw_filled_rectangle(screen_w_-60, 0, screen_w_, screen_h_, PURE_WHITE);
        al_draw_filled_rectangle(0, 0, screen_w_-60, 25, PURE_WHITE);
    }

    obstacles_.draw();
    quit_.draw();
    algorithm_.draw();
    width_.draw();
    height_.draw();
    obstacles_text_.draw();
    tracking_.draw();
    restart_.draw();
<<<<<<< HEAD
=======
    fps_label_.draw();
>>>>>>> e617387924510b31714e3f47995e77005de53387
    info_.draw();
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
    restart_.show(!show);
    play_.show(!show);
    random_.show(!show);
    speed_.show(!show);
    tracking_.show(!show);
<<<<<<< HEAD
=======
    fps_label_.show(!show);
>>>>>>> e617387924510b31714e3f47995e77005de53387
    info_.show(!show);
    step_.show(!show);
    tile_map_.show(!show);
}

////////////////////////////////////////////////////////////////////////////////

void scene::updateFPS()
{
    static uint iteration = 0;
    static double elapsed = 0;
    static double old_time = 0;

    double new_time = al_get_time();

    if (++iteration > 20)
    {
        fps_ = 20/elapsed;
        iteration = 0;
        elapsed = 0;
    }
    else
        elapsed += (new_time - old_time);

    old_time = new_time;
}

////////////////////////////////////////////////////////////////////////////////

void scene::update()
{
    updateFPS();

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

<<<<<<< HEAD
    char time_string[30];
    char fps_string[5];
    std::string search_state = result_==0 ? "Buscando camino..." : (result_==1 ? "No existe solución" : "Camino encontrado");
    std::string state = isplaying_ ? "" : "(Pausa)";
    snprintf(fps_string, sizeof(fps_string), "%2d", fps_);
    snprintf(time_string, sizeof(time_string), "%.3f %s", (time_<1 ? time_*1000 : time_), (time_<1 ? " ms" : " s"));
    info_.setText("FPS: " + std::string(fps_string) + "   " + search_state + " " + state + "  " + std::string(time_string));

    double speed;
    bool modified;
    al_lock_mutex(mutex);
    speed = speed_.getValue();
    modified = tile_map_.update();
=======
    fps_label_.setText(std::string("FPS: "+std::to_string(fps_)).c_str());

    double speed;
    al_lock_mutex(mutex);
    speed = speed_.getValue();
    tile_map_.update();
>>>>>>> e617387924510b31714e3f47995e77005de53387
    al_unlock_mutex(mutex);

    if (quit_.mouseClicked()    ) quit = true;
    if (restart_.mouseClicked() || modified) {
        al_lock_mutex(mutex);
        tile_map_.resetPlayer();
        al_unlock_mutex(mutex);
        time_ = 0;
        //isplaying_ = false;
    }
    if (random_.mouseClicked()) {
        al_lock_mutex(mutex);
        tile_map_.rebuild(width_.getValue(), height_.getValue(), obstacles_.getValue());
        al_unlock_mutex(mutex);
    }
    if (play_.mouseClicked()    ) isplaying_  = !isplaying_;
    if (tracking_.mouseClicked()) istracking_ = !istracking_;
    if (speed < 0.001           ) isplaying_  = false;

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
        (screen_h_-25)/2.0+25,
        (screen_w_-60),
        screen_h_-25
    );

<<<<<<< HEAD
    info_.resize(20,2);
=======
    info_.resize(80,2);
    fps_label_.resize(10,2);
>>>>>>> e617387924510b31714e3f47995e77005de53387
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

void scene::updateAlgorithm()
{
    double speed;
<<<<<<< HEAD
    double time_start;
    bool execute;

    al_lock_mutex(mutex);

    time_start = al_get_time();
    speed      = speed_.getValue();
    execute    = isplaying_ || step_.mouseClicked();

    if (execute)
        result_ = tile_map_.getPlayer().AStarStep();

=======
    al_lock_mutex(mutex);
    speed = speed_.getValue();
    if (isplaying_ || step_.mouseClicked())
        result_ = tile_map_.getPlayer().AStarStep();
>>>>>>> e617387924510b31714e3f47995e77005de53387
    al_unlock_mutex(mutex);

    if (execute && result_==0)
        time_ += (al_get_time() - time_start);

    double aux = 1 - speed;
    if (aux > 0.001) al_rest(aux*aux*aux);
}

////////////////////////////////////////////////////////////////////////////////
