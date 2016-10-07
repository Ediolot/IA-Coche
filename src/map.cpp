#include "map.hpp"

void map::draw() const
{
    //ALLEGRO_VERTEX v[3];

    /* = {
    {x: 128, y:   0, z: 0, color: ORANGE},
    {x:   0, y: 256, z: 0, color: ORANGE},
    {x: 256, y: 256, z: 0, color: ORANGE}
};*/
    //al_draw_prim(v, nullptr, 0, 0, 3, ALLEGRO_PRIM_TRIANGLE_LIST);
    al_draw_filled_triangle(320, 0, 640, 240, 320, 480, ORANGE);
    al_draw_filled_triangle(320, 0,   0, 240, 320, 480, ORANGE);
}
