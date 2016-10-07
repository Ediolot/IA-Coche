#ifndef UTILITY_HPP
#define UTILITY_HPP

void displayFPS(ALLEGRO_FONT *font)
{
    static double old_time = 0;
    double new_time = al_get_time();
    int fps = 1/(new_time - old_time);

    std::string stringFPS("FPS: "+std::to_string(fps));

    al_draw_text(font, PURE_WHITE, 10, 10,ALLEGRO_ALIGN_LEFT, stringFPS.c_str());

    old_time = new_time;
}

#endif
