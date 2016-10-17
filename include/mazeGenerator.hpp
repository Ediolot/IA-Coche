#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <cstdlib>
#include <ctime>
#include "common.hpp"

class mazeGenerator {

    private:
        std::vector<bool> data_;
        uint rows_;
        uint cols_;

    public:
        mazeGenerator();
        virtual ~mazeGenerator();

        void randomize(const uint rows, const uint cols, const double obst, const uint seed = 0);
        bool getPos(const uint row, const uint col) const;
};

#endif
