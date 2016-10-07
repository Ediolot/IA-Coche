#ifndef MAP_HPP
#define MAP_HPP

//#include <allegro5/allegro_primitives.h>
#include <vector>
#include <iostream> // Remove
#include "common.hpp"
#include "tile.hpp"

class map {

    const double BORDER = 0.1;

    private:

        std::vector<tile> tiles_;
        point vertices_[4];
        uint size_;

    public:

        map(const uint size, const double screenWidth, const double screenHeight, const double percent = 0.9);
        virtual ~map();

        void draw() const;
};

#endif
