#ifndef SCENE_HPP
#define SCENE_HPP

#include <allegro5/allegro.h>
#include "common.hpp"
#include "map.hpp"

class scene {

    private:
        map tile_map_;
        double map_separation_;
        uint screen_w_;
        uint screen_h_;
        uint map_size_;
        double inc_x_;
        double inc_y_;

    public:
        scene(const uint screen_w, const uint screen_h, const uint map_size, const double tiles_separation, const double map_separation);
        virtual ~scene();

        void generate(const uint rivers, const uint min_size_river, const bool accumulative_rivers);
        void draw() const;

        void moveX(const double x);
        void moveY(const double y);
};

#endif
