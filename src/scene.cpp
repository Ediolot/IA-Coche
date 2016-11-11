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

    info_("FPS: 0", al_map_rgb(0,0,0), caviar_font_16),
    fps_(0),
    result_(0),
    time_(0),

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

    info_.resize(20,2);
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

#include <fstream>
#include <iostream>
void scene::updateAlgorithm()
{
    double speed;
    double time_start;
    bool execute;

    al_lock_mutex(mutex);

    time_start = al_get_time();
    speed      = speed_.getValue();
    execute    = isplaying_ || step_.mouseClicked();

    if (execute)
        result_ = tile_map_.getPlayer().AStarStep();

    al_unlock_mutex(mutex);

    if (execute && result_==0)
        time_ += (al_get_time() - time_start);

    double aux = 1 - speed;
    if (aux > 0.001) al_rest(aux*aux*aux);

    //////////////////// TESTS
    static std::ofstream output("output.txt");
    const int max_sz = 200;
    const int max_tests = 8;
    const double max_obs = 0.8;

    const int sz_steps = 10;
    const int obs_steps = 16;

    const int sz_inc = max_sz / sz_steps;
    const double obs_inc = max_obs / obs_steps;

    static int sz = 1;
    static int obs = 0;
    static int test = 0;

    static bool reset = true;
    static bool first = true;
    static bool end = false;

    typedef std::vector<double> tests_row;
    typedef std::vector<tests_row> serie;
    static std::vector<serie> series;

    if (end)
        return;
    else
        al_lock_mutex(mutex);

    if (execute)
    {
        if (first)
        {
            first = false;

            tests_row empty_row;
            serie empty_serie;
            empty_serie.push_back(empty_row);
            series.push_back(empty_serie);
        }
        if (reset)
        {
            tile_map_.rebuild(sz * sz_inc, sz * sz_inc, obs*obs_inc);
            tile_map_.rebuild(sz * sz_inc, sz * sz_inc, obs*obs_inc);
            tile_map_.rebuild(sz * sz_inc, sz * sz_inc, obs*obs_inc);
            tile_map_.rebuild(sz * sz_inc, sz * sz_inc, obs*obs_inc);
            time_ = 0;
            reset = false;
        }
        else if (result_!=0 && !end)
        {
            int max = obs==0 ? 0 : (obs==1 ? 3 : (obs==2 ? 5 : max_tests));
            std::cout << "test: "   << max         << "/" << max_tests;
            std::cout << "  size: " << sz*sz_inc   << "/" << max_sz;
            std::cout << "  obs: "  << obs*obs_inc << "/" << max_obs;
            std::cout << "  time: " << time_;
            std::cout << "  found: " << (result_==2 ? "yes" : "no") << std::endl;

            series[obs][sz-1].push_back(result_==2 ? time_ : -1);

            reset = true;
            if (++test > max)
            {
                test = 0;

                tests_row empty_row;
                series[obs].push_back(empty_row);

                if (++sz*sz_inc > max_sz)
                {

                    sz = 1;
                    end = ++obs*obs_inc > max_obs;
                    if (!end)
                    {
                        tests_row empty_row;
                        serie empty_serie;
                        empty_serie.push_back(empty_row);
                        series.push_back(empty_serie);
                    }
                    else
                    {
                        for (serie &s : series)
                        {
                            for (int sz_1 = 0; (sz_1*sz_inc) < max_sz; ++sz_1)
                            {
                                for (double t : s[sz_1]) output << (sz_1+1) * sz_inc << "," << t << "\n";
                            }
                            output << "\n";
                            output << "\n";
                            output << "\n";
                        }
                        output.close();
                    }
                }
            }
        }
    }

    al_unlock_mutex(mutex);
}

////////////////////////////////////////////////////////////////////////////////
