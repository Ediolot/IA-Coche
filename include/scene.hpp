#ifndef SCENE_HPP
#define SCENE_HPP

#include <allegro5/allegro.h>
#include "common.hpp"
#include "map.hpp"

class scene {

    private:
        map tile_map_;          // Tiles map
        double map_separation_; // Tiles map's separation from the borders of the window
        uint screen_w_;
        uint screen_h_;
        uint map_size_;         // Number of tiles in the side of the map
        double inc_x_;
        double inc_y_;

    public:
        scene(const uint screen_w, const uint screen_h, const uint map_size, const double tiles_separation, const double map_separation);
        virtual ~scene();

        // Genera los elementos de la escena
        void generate(const uint rivers, const uint min_size_river, const bool accumulative_rivers);

        // Dibuja los elementos de la escena
        void draw() const;

        // Mueve la escena en x o y
        void moveX(const double x);
        void moveY(const double y);
};

#endif
